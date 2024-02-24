#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <queue>
#include "RayScene.h"
#include "LightSource.h"
#include "DirectionalLight.h"
#include "Spotlight.h"
#include "Sphere.h"
#include "RayPlane.h"

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{ 	
}

void Game::LoadSceneFile(const std::string& fileName){
    rayScene = RayScene();
    std::fstream sfile;
    sfile.open(fileName);

    //get first line
    std::string eye;
    float xe, ye, ze, we;
    std::getline(sfile, eye);
    sscanf(eye.c_str(), "e %f %f %f %f", &xe, &ye, &ze, &we);
    rayScene.setCamera(xe, ye, ze);

    //get second line
    std::string ambient;
    float r, g, b, a;
    std::getline(sfile, ambient);
    sscanf(ambient.c_str(), "a %f %f %f %f", &r, &g, &b, &a);
    rayScene.setAmbient(r, g, b);

    //get objects/lights
    std::string currLine;
    char id;
    float p1, p2, p3, p4;
    int intensityI = 0;
    int currL = 0;
    int colorI = 0;
    std::queue<int> spotlightIndexes = std::queue<int>();
    while(std::getline(sfile, currLine)) {
        sscanf(currLine.c_str(), "%c %f %f %f %f", &id, &p1, &p2, &p3, &p4);
        switch(id){
            case 'd':
                if(p4 == 0.0){
                    LightSource* l = new DirectionalLight();
                    l->setDirection(p1, p2, p3);
                    rayScene.addLightSource(l);
                } else if(p4 == 1){
                    LightSource* l = new Spotlight();
                    l->setDirection(p1, p2, p3);
                    rayScene.addLightSource(l);
                    spotlightIndexes.push(currL);
                }
                currL++;
                break;
            case 'p':
                rayScene.addSpotlightPos(spotlightIndexes.front(), p1, p2, p3);
                rayScene.addSpotlightAlpha(spotlightIndexes.front(), p4);
                spotlightIndexes.pop();
                break;
            case 'i':
                rayScene.addLightSourceIntensity(intensityI, p1, p2,p3);
                intensityI++;
                break;
            case 'o':
                if(p4 > 0){ //is a sphere
                    RayObject* o = new Sphere(p1,p2,p3,p4);
                    rayScene.addObject(o);
                } else {
                    RayObject* o = new RayPlane(p1,p2,p3,p4);
                    rayScene.addObject(o);
                }
                break;
            case 'r':
                if(p4 > 0){ //is a sphere
                    RayObject* o = new Sphere(p1,p2,p3,p4);
                    o->setR();
                    rayScene.addObject(o);
                } else {
                    RayObject* o = new RayPlane(p1,p2,p3,p4);
                    o->setR();
                    rayScene.addObject(o);
                }
                break;
            case 't':
                if(p4 > 0){ //is a sphere
                    RayObject* o = new Sphere(p1,p2,p3,p4);
                    o->setT();
                    rayScene.addObject(o);
                } else {
                    RayObject* o = new RayPlane(p1,p2,p3,p4);
                    o->setT();
                    rayScene.addObject(o);
                }
                break;
            case 'c':
                rayScene.setObjectColor(colorI, p1, p2, p3, p4);
                colorI++;
                break;
        }
    }
}

void Game::Init()
{		
   

	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader");

    int width = 800;
    int height = 800;
	//AddTexture("../res/textures/box0.bmp",false);
    system("cd");
    LoadSceneFile("../inputs/custom_scene.txt");

    //Test:
    printf("printing\n");
    rayScene.printData();

    unsigned char* data = rayScene.render(width,height); //TODO: implement Render -- main algo
    AddTexture(width, height, data);
    free(data);
    AddShape(Plane,-1,TRIANGLES);

    pickedShape = 0;

    SetShapeTex(0,0);
    MoveCamera(0,zTranslate,10);
    pickedShape = -1;
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else 
		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
	}
}

Game::~Game(void)
{
}
