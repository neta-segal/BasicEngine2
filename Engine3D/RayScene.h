//
// Created by Neta Segal on 21/02/2024.
//

#ifndef GAME_RAYSCENE_H
#define GAME_RAYSCENE_H
#include "RayCamera.h"
#include "Ambient.h"
#include "LightSource.h"
#include "RayObject.h"
#include <vector>


class RayScene {

public:
    RayScene(){
        camera = RayCamera(0,0,0);
        objects = std::vector<RayObject*>();
        lightSources = std::vector<LightSource*>();
    }
    void setCamera(float x, float y, float z);
    void setAmbient(float r, float g, float b);
    void addLightSource(LightSource* l);
    void addObject(RayObject* o);
    void addSpotlightPos(int index, float x, float y, float z);
    void addSpotlightAlpha(int index, double a);
    void addLightSourceIntensity(int index, float r, float g, float b);
    void setObjectColor(int index, float r, float g, float b, float i);

    unsigned char* render(int width, int height);
    void printData();
    glm::vec3 calcPixel(const glm::vec3& eye, const glm::vec3& ray_dir, unsigned char calls_left, RayObject* inside_obj);
    glm::vec3 snells_law(glm::vec3 N, glm::vec3 S1, float n1, float n2);


private:
    RayCamera camera;
    Ambient ambient;
    std::vector<LightSource*> lightSources;
    std::vector<RayObject*> objects;

};

//TODO: make a constructor that earases the light sources and objects


#endif //GAME_RAYSCENE_H
