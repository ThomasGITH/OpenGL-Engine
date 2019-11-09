#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <memory>
#include "game_objects_incl.h"
#include "Shader.h"
#include "Input.h"
#include "GameObject.h"

class Locator;

class GameManager
{
public:
	GameManager(){}
	GameManager(GLint bufferWidth, GLint bufferHeight, GLFWwindow* mainWindow);

	void Update();
	void CreateShaders();
	void ClearHeap();

	std::vector<GameObject*>& GetGameObjectList() { return _gameObjList; };
	
	void CompileIndividualLights();

	Input* inputManager;

	~GameManager();
private:

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformDLColour = 0, uniformDLAmbientIntensity = 0,
		uniformDLDirection = 0, uniformDLDiffuseIntensity = 0, uniformSpecularIntensity, uniformShinyness, uniformEyePosition;

	Player* player = new Player(glm::vec3(-4.0f, 1.5f, -2.0f), 0.0f);
	Lantern* lantern = new Lantern(glm::vec3(0.0f, 0.0f, -2.5), glm::vec3(1.0f, 0.2f, 1.0f), 0.3f, 0.2f, 0.1f);
	Lantern* otherLantern = new Lantern(glm::vec3(2.0f, 0.0f, -2.5), glm::vec3(0.0f, 1.0f, 0.0f), 0.3f, 0.2f, 0.1f);
	Test* test = new Test(glm::vec3(1.0f, -0.5f, -2.5f), 270.0f, "Textures/plain.png");
	Test* otherTest = new Test(glm::vec3(-1.0f, -0.5f, -2.5f), 0.0f, "Textures/brick.png");
	Sun* sun = new Sun(glm::vec3(1.0f, 1.0f, 1.0f),0.5f, glm::vec3(0.0f,0.0f,-1.0f), 0.0f);
	
	Platform* platform = new Platform(glm::vec3(1.0f, -1.0f, -2.0f));
	
	FlashLight* flashLight = new FlashLight(glm::vec3(2.0f, 2.0f, 0.78f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f);
	FlashLight* mySpotLight = new FlashLight(glm::vec3(-1.3f, 2.0f, -4.7f), glm::vec3(1.0f, 1.0f, 1.0f), 0.3f, 0.2f, 0.1f);
	Dragon* dragon = new Dragon(glm::vec3(0.0f, -1.0f, -0.0f));

	glm::mat4 model, projection;
	std::vector<Shader> shaderList;
	std::vector<GameObject*> _gameObjList, _pointLightList, _spotLightList;

	GLfloat deltaTime = 0.0f, lastTime = 0.0f;

	bool* keys;
};
