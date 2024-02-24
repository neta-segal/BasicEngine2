//
// Created by Neta Segal on 21/02/2024.
//

#include "LightSource.h"

void LightSource::setDirection(float x, float y, float z){direction = glm::vec3(x,y,z);}
void LightSource::setIntensity(float r, float g, float b){intensity = glm::vec3(r,g,b);}
void LightSource::printData() {
    std::cout << "direction: " << glm::to_string(direction) << std::endl;
    std::cout << "intensity: " << glm::to_string(intensity) << std::endl;
}