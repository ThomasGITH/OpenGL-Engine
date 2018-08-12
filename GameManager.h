#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm\glm.hpp>
#include "Player.h"
#include "Test.h"
#include "Sun.h"
#include "Shader.h"
#include "Input.h"
#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

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
	
	Input* inputManager;

	~GameManager();
private:

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientColour, uniformAmbientIntensity,
		uniformDirection, uniformDiffuseIntensity;

	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	Test* test = new Test(glm::vec3(1.0f, 0.5f, -2.5f), 270.0f);
	Sun* sun = new Sun(glm::vec3(1.0f,1.0f,1.0f),0.2f, glm::vec3(0.0f,0.0f,-1.0f), 0.5f);

	glm::mat4 inputModel, outputModel, projection;
	std::vector<GameObject*> _gameObjList;
	std::vector<Shader> shaderList;

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	bool* keys;
};