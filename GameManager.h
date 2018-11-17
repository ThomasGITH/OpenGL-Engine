#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm\glm.hpp>
#include "Player.h"
#include "Test.h"
#include "Sun.h"
#include "Shader.h"
#include "Input.h"
#include "Platform.h"
#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Light.h"
#include "Lantern.h"
#include "FlashLight.h"

class Locator;

class GameManager
{
public:
	GameManager(){}
	GameManager(GLint bufferWidth, GLint bufferHeight, GLFWwindow* mainWindow);

	void Update();
	void CreateShaders();
	void ClearHeap();

	std::vector<GameObject*> GetGameObjectList() { return _gameObjList; };
	void SetGameObjectList(std::vector<GameObject*> list) { _gameObjList = list; };
	
	void CompileIndividualLights();

	Input* inputManager;

	~GameManager();
private:

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformDLColour = 0, uniformDLAmbientIntensity = 0,
		uniformDLDirection = 0, uniformDLDiffuseIntensity = 0, uniformSpecularIntensity, uniformShinyness, uniformEyePosition;

	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	Lantern* lantern = new Lantern(glm::vec3(0.0f, 0.0f, -2.5), glm::vec3(1.0f, 0.2f, 1.0f), 0.3f, 0.2f, 0.1f);
	Lantern* otherLantern = new Lantern(glm::vec3(2.0f, 0.0f, -2.5), glm::vec3(0.0f, 1.0f, 0.0f), 0.3f, 0.2f, 0.1f);
	Test* test = new Test(glm::vec3(1.0f, -0.5f, -2.5f), 270.0f, "Textures/plain.png");
	Test* otherTest = new Test(glm::vec3(-1.0f, -0.5f, -2.5f), 0.0f, "Textures/brick.png");
	Sun* sun = new Sun(glm::vec3(1.0f, 1.0f, 1.0f),0.2f, glm::vec3(0.0f,0.0f,-1.0f), 0.0f);
	Platform* platform = new Platform(glm::vec3(1.0f, -1.0f, -2.0f));
	FlashLight* flashLight = new FlashLight(glm::vec3(2.0f, 2.0f, 0.78f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f);
	FlashLight* mySpotLight = new FlashLight(glm::vec3(-1.3f, 2.0f, -4.7f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f);

	glm::mat4 inputModel, outputModel, projection;
	std::vector<GameObject*> _gameObjList, _pointLightList, _spotLightList;
	std::vector<Shader> shaderList;

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	bool* keys;
};