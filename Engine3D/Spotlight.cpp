//
// Created by Neta Segal on 21/02/2024.
//

#include "Spotlight.h"

void Spotlight::setPosition(float x, float y, float z){position = glm::vec3(x,y,z);}

void Spotlight::setAlpha(double a) {
    alpha = a;
}

void Spotlight::printData() {
    printf("SpotLight: \n");
    LightSource::printData();

    std::cout << "position: " << glm::to_string(position) << std::endl;
    printf("alpha: %f\n", alpha);
}

glm::vec3 Spotlight::calcPhong(const glm::vec3& eye, RayObject* obj, const glm::vec3& inter_point) {

    //add check that it is in spotlight
    glm::vec3 v = glm::normalize(inter_point - this->position);
    //float theta = glm::dot(v, glm::normalize(-direction));
    double thetacos = (glm::dot(direction, v)/(glm::length(direction)*glm::length(v)));
    if (thetacos <= alpha) {
        return glm::vec3(0,0,0);
    }

    glm::vec3 N = glm::normalize(obj->normal(inter_point));
    //glm::vec3 L = glm::normalize(-direction);
    glm::vec3 L = glm::normalize(position - inter_point);;

    float diffuse_dot = glm::max(glm::dot(L, N), 0.0f);
    glm::vec3 diffuse = diffuse_dot * obj->getColor(inter_point) * intensity;

    //if (diffuse.x > 0.0 || diffuse.y > 0.0 || diffuse.z > 0.0)printf("Ilegal Diffuse\n");

    //R might be incorrect as the direction of the normal relative to the surface is ambiguous - make sure to think through
    glm::vec3 R = glm::normalize(2.0f * glm::dot(N, L) * N - L);
    glm::vec3 V = glm::normalize(eye - inter_point);
    float specular_dot = glm::max(glm::dot(R, V), 0.0f); // Ensure non-negative
    glm::vec3 specular = std::pow(specular_dot, obj->getAlpha()) * glm::vec3(0.7, 0.7, 0.7) * intensity;
    return diffuse + specular;
}
