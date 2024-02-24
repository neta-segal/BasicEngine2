//
// Created by Neta Segal on 21/02/2024.
//

#include "DirectionalLight.h"

void DirectionalLight::printData() {
    printf("DirectionalLight: \n");
    LightSource::printData();
}

glm::vec3 LightSource::calcPhong(const glm::vec3& eye, RayObject* obj, const glm::vec3& inter_point) {

    glm::vec3 N = glm::normalize(obj->normal(inter_point));
    glm::vec3 L = glm::normalize(-direction);

    float diffuse_dot = glm::max(glm::dot(L, N), 0.0f);
    glm::vec3 diffuse = diffuse_dot * obj->getColor(inter_point) * intensity;

    //R might be incorrect as the direction of the normal relative to the surface is ambiguous - make sure to think through
    glm::vec3 R = glm::normalize(2.0f * glm::dot(N, L) * N - L);
    glm::vec3 V = glm::normalize(eye - inter_point);
    float specular_dot = glm::max(glm::dot(R, V), 0.0f); // Ensure non-negative
    glm::vec3 specular = std::pow(specular_dot, obj->getAlpha()) * glm::vec3(0.7, 0.7, 0.7) * intensity;
    return diffuse + specular;

}