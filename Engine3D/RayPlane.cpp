//
// Created by Neta Segal on 22/02/2024.
//

#include "RayPlane.h"
void RayPlane::printData() {
    printf("Plane: \n");
    RayObject::printData();

    std::cout << "eq: " << glm::to_string(eq) << std::endl;
    printf("d: %f\n", d);
}

//huh?????
glm::vec3 RayPlane::getColor(glm::vec3 inter_point){

    //based on https://www.ronja-tutorials.com/post/011-chessboard/
    float scale = 0.5f;
    float check = 0;
    //if negative needs to be the opposite color
    check += floor(((inter_point.x < 0) ? (0.5 - inter_point.x) : inter_point.x) / scale) + floor(((inter_point.y < 0)? (0.5 - inter_point.y) : inter_point.y) / scale);

    check = std::fmod(check * 0.5, 1.0) * 2.0f;
    return (check >= 0.5) ? 0.5f * rgb : rgb;
}

//Returns the minimal non-negative t for which A+t*B is on the plane
float RayPlane::intersect(glm::vec3 A, glm::vec3 B) {
    float denom = glm::dot(eq, B);
    if (denom < 0.0001f)return -1.0;
    float res = -(glm::dot(eq, A) + d) / denom;
    if (res <= 0.001f) {
        return -1.0;
    }
    return res;
}

glm::vec3 RayPlane::normal(glm::vec3 point) {
    if (glm::dot(eq, point) > 0.0001f)return -eq;
    return eq;
}