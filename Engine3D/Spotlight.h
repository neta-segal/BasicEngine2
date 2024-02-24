//
// Created by Neta Segal on 21/02/2024.
//

#ifndef GAME_SPOTLIGHT_H
#define GAME_SPOTLIGHT_H
#include "LightSource.h"
#include "../res/includes/glm/glm.hpp"


class Spotlight : public LightSource{
public:
    glm::vec3 position;
    double alpha;

    Spotlight()= default;
    void setPosition(float x, float y, float z);
    void setAlpha(double a);

    void printData();

	virtual glm::vec3 calcPhong(const glm::vec3& eye, RayObject* obj, const glm::vec3& inter_point);
};


#endif //GAME_SPOTLIGHT_H
