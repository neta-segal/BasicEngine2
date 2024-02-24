//
// Created by Neta Segal on 21/02/2024.
//

#ifndef GAME_DIRECTIONALLIGHT_H
#define GAME_DIRECTIONALLIGHT_H
#include "LightSource.h"

#include "RayObject.h"

#include<iostream>
#include<string>
class DirectionalLight : public LightSource{
public:
    void printData();
    glm::vec3 calcPhong(const glm::vec3& eye, RayObject* obj, const glm::vec3& inter_point) {
        return LightSource::calcPhong(eye, obj, inter_point);
    }
};


#endif //GAME_DIRECTIONALLIGHT_H
