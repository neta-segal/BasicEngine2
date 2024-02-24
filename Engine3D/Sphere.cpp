//
// Created by Neta Segal on 22/02/2024.
//

#include "Sphere.h"

glm::vec3 Sphere::getColor(glm::vec3 hit){
    return rgb;
}

void Sphere::printData() {
    printf("Sphere: \n");
    RayObject::printData();

    std::cout<< "pos: " << glm::to_string(pos) << std::endl;
    printf("rad: %f\n", radius);
}

//https://raytracing.github.io/books/RayTracingInOneWeekend.html#addingasphere/ray-sphereintersection
//Returns the minimal non-negative t for which A+t*B is on the sphere
float Sphere::intersect(glm::vec3 A, glm::vec3 B){
    float a = glm::dot(B, B);
    float b = 2.0*glm::dot(B,A-pos);
    float c = glm::dot(A - pos, A - pos) - radius * radius;

    float det = b * b - 4 * a * c;
    if (det < 0)return -1.0;
    det = sqrt(det);
    float small = (- b - det)/2.0/a;
    if (small >= 0.001f)return small;
    float res = (-b + det) / 2.0 / a;
    if (res <= 0.001f) {
        return -1.0;
    }
    return res;
}

glm::vec3 Sphere::normal(glm::vec3 point) {
    return point-pos;
}
