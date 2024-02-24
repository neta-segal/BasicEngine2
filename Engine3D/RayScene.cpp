//
// Created by Neta Segal on 21/02/2024.
//

#include "RayScene.h"
#include "Spotlight.h"
#include "DirectionalLight.h"
#include "Sphere.h"

void RayScene::setCamera(float x, float y, float z){camera = RayCamera(x, y, z);}

void RayScene::setAmbient(float r, float g, float b){ambient = Ambient(r, g, b);}

void RayScene::addLightSource(LightSource* l){
    lightSources.push_back(l);
}

void RayScene::addSpotlightPos(int index, float x, float y, float z) {
    ((Spotlight*) lightSources[index])->setPosition(x,y,z);
}

void RayScene::addSpotlightAlpha(int index, double a) {
    ((Spotlight*) lightSources[index])->setAlpha(a);
}

void RayScene::addLightSourceIntensity(int index, float r, float g, float b) {
    lightSources[index]->setIntensity(r,g,b);
}

void RayScene::addObject(RayObject *o) {
    objects.push_back(o);
}

void RayScene::setObjectColor(int index, float r, float g, float b, float a) {
    objects[index]->setColor(r,g,b,a);
}

void RayScene::printData() {
    camera.printData();
    printf("\n");

    ambient.printData();
    printf("\n");

    printf("numObjects: %d\n", objects.size());
    for (RayObject* o : objects) {
        o->printData();
        printf("\n");
    }
    printf("numLightSources: %d\n", lightSources.size());
    for (LightSource* l : lightSources) {
        l->printData();
        printf("\n");
    }
}


void setPixel(unsigned char* image, int w, int h, int i, int j, glm::vec3 rgb) {
    int index = 4 * (j + i * h);
    if (index >= 4 * w * h)return;
    image[index] = (unsigned char)(0.5 + 255.0*rgb.x);
    image[index + 1] = (unsigned char)(0.5 + 255.0 * rgb.y);
    image[index + 2] = (unsigned char)(0.5 + 255.0 * rgb.z);
    image[index + 3] = 255;
}

unsigned char getPixel(unsigned char* image, int w, int h, int i, int j) {
    return image[4 * (j + i * h)];
}

//S1 goes in the material, N is the normal pointing outside of the matrial
// ASSUMES N AND S1 ARE NORMALIZED
//Based on https://www.starkeffects.com/snells-law-vector.shtml#:~:text=Snell's%20Law%20in%20Vector%20Form,wavelength%20of%20light%20being%20transmitted.
glm::vec3 RayScene::snells_law(glm::vec3 N, glm::vec3 S1, float n1, float n2) {
    float q = n1 / n2;
    glm::vec3 NcS1 = glm::cross(N, S1);
    return q * glm::cross(N, -NcS1) - N * std::sqrt(1 - q * q * glm::dot(NcS1, NcS1));
}

glm::vec3 RayScene::calcPixel(const glm::vec3& eye, const glm::vec3& ray_dir, unsigned char calls_left, RayObject* inside_obj) {
    RayObject* inter_obj = 0;
    float min_t = -1.0;
    for (RayObject* obj : objects) {
        //Get the smallest non negtive t for which eye+t*ray_dir=[point on obj]
        float t = obj->intersect(eye,ray_dir);
        if (t > 0) {
            //printf("tracing %f %f %f\n", spoint.x, spoint.y, spoint.z);
            //printf("t: %f\n", t);
        }
        if ((t < min_t && t>=0) || min_t < 0) {
            inter_obj = obj;
            min_t = t;
        }
    }

    if (min_t < 0)return glm::vec3(0,0,0); // No intersection
    //printf("min_t: %f\n", min_t);

    glm::vec3 inter_point = eye + ray_dir * min_t;

    //If reflective
    if (inter_obj->getR()) {
        if(calls_left>0){
            glm::vec3 N = glm::normalize(inter_obj->normal(inter_point));
            glm::vec3 L = glm::normalize(-ray_dir);
            glm::vec3 R = glm::normalize(2.0f * glm::dot(N, L) * N - L);
            return calcPixel(inter_point, R, calls_left - 1, 0);
        }
        else {
            return glm::vec3(0, 0, 0);
        }
    }

    //If transparent - use Snell's law
    if (inter_obj->getT()) {
        if (inside_obj) {
            //printf("going out\n");
            //std::cout << glm::to_string(inter_point) << std::endl;
            return calcPixel(inter_point, snells_law(glm::normalize(-inter_obj->normal(inter_point)), glm::normalize(ray_dir), 1.5, 1.0f), calls_left, 0);
        }
        else {
            //printf("going in\n");
            //std::cout << glm::to_string(inter_point) << std::endl;
            return calcPixel(inter_point, snells_law(glm::normalize(inter_obj->normal(inter_point)), glm::normalize(ray_dir), 1.0f, 1.5f), calls_left, dynamic_cast<Sphere*>(inter_obj));
        }
    }

    glm::vec3 phong_intensity = ambient.point*inter_obj->getColor(inter_point);

    for (LightSource* ls : lightSources) {
        bool isFirst = true;
        if (dynamic_cast< Spotlight *>(ls) != nullptr) {
            Spotlight * spotlight = dynamic_cast< Spotlight *>(ls);
            glm::vec3 v = inter_point - spotlight->position;
            for (RayObject *obj: objects) {
                if (obj->intersect(spotlight->position, v)>0 && inter_obj->intersect(spotlight->position, v) > obj->intersect(spotlight->position, v)){
                    isFirst = false;
                    break;
                }
            }
        } else if (dynamic_cast< DirectionalLight *>(ls) != nullptr) {
            glm::vec3 v = -ls->direction ;
            for (RayObject *obj: objects) {
                if (obj->intersect(inter_point, v)>0 && obj != inter_obj){
                    isFirst = false;
                    break;
                }
            }
        }
        if(isFirst) phong_intensity += ls->calcPhong(eye, inter_obj, inter_point);
    }

    return glm::clamp(phong_intensity, 0.0f, 1.0f);
    //printf("color %f %f %f\n", inter_obj->getColor().x, inter_obj->getColor().y, inter_obj->getColor().z);
    //return inter_obj->getColor();
}

unsigned char* RayScene::render(const int width, const int height) {
    unsigned char* image = (unsigned char*)malloc(width * height * 4 * sizeof(unsigned char));
   
    //point on screen
    glm::vec3 spoint(0,1-1.0/height,0);
    for (int i = 0; i < height; i++) {
        spoint.x = -1 + 1.0 / width;
        for (int j = 0; j < width; j++) {
            //printf("(%f, %f, %f)\n", spoint.x, spoint.y, spoint.z);
            setPixel(image, width, height, i, j, calcPixel(camera.point, spoint - camera.point, 5, 0));
            spoint.x += 2.0 / width;
        }
        spoint.y -= 2.0 / height;
    }

    return image;
}
