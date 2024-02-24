//
// Created by Neta Segal on 22/02/2024.
//

#include "RayObject.h"
#include <stdio.h>
void RayObject::setR(){reflective = true;}
void RayObject::setT(){transparent =true;}

void RayObject::setColor(float r, float g, float b, float a) {
    this->rgb = glm::vec3(r, g, b);
    this->a = a;
}

float RayObject::getAlpha() {
    return a;
}

void RayObject::printData() {
    printf("rgba = %f %f %f %f\n",rgb.r,rgb.g,rgb.b,a);
}

bool RayObject::getR() {
    return reflective;
}

bool RayObject::getT() {
    return transparent;
}