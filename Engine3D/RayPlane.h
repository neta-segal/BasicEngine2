//
// Created by Neta Segal on 22/02/2024.
//

#ifndef GAME_RAYPLANE_H
#define GAME_RAYPLANE_H
#include "RayObject.h"
#include "../res/includes/glm/glm.hpp"

//For glm::to_string
#include <glm/gtx/string_cast.hpp>

class RayPlane : public RayObject{

public:
    RayPlane(float a, float b, float c, float d){
        this->eq = glm::vec3(a,b,c);
        this->d = d;
    }
    void printData();
    glm::vec3 getColor(glm::vec3 inter_point) override;
    float intersect(glm::vec3 A, glm::vec3 B) ; //Returns the minimal non-negative t for which A+t*B is on the plane
    glm::vec3 normal(glm::vec3 point) ;

private:
    glm::vec3 eq;
    float d;
};


#endif //GAME_RAYPLANE_H
