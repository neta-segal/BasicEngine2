//
// Created by Neta Segal on 21/02/2024.
//

#include "RayCamera.h"

void RayCamera::printData() const {
    printf("Camera: \n");

    std::cout << "point: " << glm::to_string(point) << std::endl;
}