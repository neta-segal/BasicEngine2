//
// Created by Neta Segal on 21/02/2024.
//

#ifndef GAME_AMBIENT_H
#define GAME_AMBIENT_H
#include "../res/includes/glm/glm.hpp"

//For glm::to_string
#include <glm/gtx/string_cast.hpp>
#include <string>
#include <iostream>

class Ambient {

public:
    //Not vec4 as a=1
    glm::vec3 point;
    Ambient(){}
    Ambient(float r, float g ,float b){point = glm::vec3(r, g, b);}

    void printData() {
        printf("Ambient: \n");

        std::cout << "point: " << glm::to_string(point) << std::endl;
    }

};


#endif //GAME_AMBIENT_H
