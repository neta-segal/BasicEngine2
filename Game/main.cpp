
#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>
#include <fstream>

#include "InputManager.h"
// #include "../DisplayGLFW/display.h"
#include "game.h"
#include "../res/includes/glm/glm.hpp"
#include "stb_image.h"



int main(int argc,char *argv[])
{

    //parser
    const int DISPLAY_WIDTH = 800;
    const int DISPLAY_HEIGHT = 800;
    const float CAMERA_ANGLE = 0.0f;
    const float NEAR = 1.0f;
    const float FAR = 100.0f;

    Game *scn = new Game(CAMERA_ANGLE,(float)DISPLAY_WIDTH/DISPLAY_HEIGHT,NEAR,FAR);

    Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

    Init(display);

    scn->Init();

    display.SetScene(scn);

    //std::string lenaFile = "../res/textures/lena256.jpg";
    //int width, height, numComponents;
    //unsigned char* data1 = stbi_load((&lenaFile)->c_str(), &width, &height, &numComponents, 4);

    //regular lena
    //scn->AddTexture(lenaFile, false);
    //scn->SetShapeTex(0,0);
    //scn->Draw(1, 0, Game::BACK, true, false);


   // scn->Motion();
    //display.SwapBuffers();

    while(!display.CloseWindow())
    {
        scn->Draw(1,0,scn->BACK,true,false);
        scn->Motion();
        display.SwapBuffers();
        display.PollEvents();

    }
    delete scn;
    return 0;
}


void convolution(const unsigned char* grayscale, const float* kernel, unsigned char* result) {
    const int width = 256;
    const int height = 256;
    int count = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int sum = 0;
            for (int k = 0; k < 3; ++k) { //row i
                for (int l = 0; l < 3; ++l) { //element ij
                    int imagei = (i + k - 1);
                    int imagej = (j + l - 1);
                    if (imagei < 0) imagei = 1;
                    if (imagej < 0) imagej = 1;
                    if (imagei >= height) imagei = height - 1;
                    if (imagej >= width) imagej = width - 1;
                    sum += grayscale[imagei * width + imagej] * kernel[k * 3 + l];
                }
            }
            count++;
            result[i * (width)+j] = sum;
        }
    }

}