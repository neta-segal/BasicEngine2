//
// Created by Neta Segal on 22/02/2024.
//

#ifndef GAME_SPHERE_H
#define GAME_SPHERE_H
#include "RayObject.h"
#include "../res/includes/glm/glm.hpp"

//For glm::to_string
#include <glm/gtx/string_cast.hpp>


class Sphere : public RayObject{
public:
    Sphere(float x, float y, float z, float r){
        this->pos = glm::vec3(x,y,z);
        this->radius = r;
    }

    glm::vec3 getColor(glm::vec3 hit);
    void printData();
    float intersect(glm::vec3 A, glm::vec3 B);
    glm::vec3 normal(glm::vec3 point);
private:
    glm::vec3 pos;
    float radius;
};


#endif //GAME_SPHERE_H
