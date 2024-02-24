//
// Created by Neta Segal on 22/02/2024.
//

#ifndef GAME_RAYOBJECT_H
#define GAME_RAYOBJECT_H

#include <iostream>
#include <string>
#include <glm/glm.hpp>



class RayObject {


public:
    RayObject(){reflective = false; transparent = false;}
    void setR();
    void setT();
    void setColor(float r, float g,float b,float a);
    float getAlpha();
    virtual void printData();
    virtual float intersect(glm::vec3 A, glm::vec3 B) = 0;
    virtual glm::vec3 normal(glm::vec3 point) = 0;
    virtual glm::vec3 getColor(glm::vec3 hit) = 0;
    bool getR();
    bool getT();
private:
    bool reflective;
    bool transparent;
    float a;
protected:
    glm::vec3 rgb;
};


#endif //GAME_RAYOBJECT_H
