//
// Created by Neta Segal on 21/02/2024.
//

#ifndef GAME_RAYCAMERA_H
#define GAME_RAYCAMERA_H
#include "../res/includes/glm/glm.hpp"

//For glm::to_string
#include <glm/gtx/string_cast.hpp>
#include <string>
#include <iostream>

class RayCamera {

public:
    glm::vec3 point;

    RayCamera()= default;
    RayCamera(float x, float y ,float z){point = glm::vec3(x, y, z);}

    void printData() const;
};


#endif //GAME_RAYCAMERA_H
