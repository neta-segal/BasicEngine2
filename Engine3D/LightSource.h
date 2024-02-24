//
// Created by Neta Segal on 21/02/2024.
//

#ifndef GAME_LIGHTSOURCE_H
#define GAME_LIGHTSOURCE_H
#include "../res/includes/glm/glm.hpp"

#include <iostream>
#include <string>
#include <glm/gtx/string_cast.hpp>

#include <math.h>

#include "RayObject.h"
class LightSource {
public:
    glm::vec3 direction;
    glm::vec3 intensity;
    LightSource(){}
    void setDirection(float x, float y, float z);
    void setIntensity(float r, float g, float b);
    virtual void printData();
    virtual glm::vec3 calcPhong(const glm::vec3& eye, RayObject* obj, const glm::vec3& inter_point) = 0;
};


#endif //GAME_LIGHTSOURCE_H
