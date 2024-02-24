#pragma once
#include "scene.h"
#include "RayScene.h"

class Game : public Scene
{
public:

	Game();
	Game(float angle,float relationWH,float near, float far);
    void LoadSceneFile(const std::string& fileName);
	void Init();
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	void ControlPointUpdate();
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	~Game(void);

private:
    RayScene rayScene;
};

