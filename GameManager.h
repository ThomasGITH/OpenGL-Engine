#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm\glm.hpp>
#include "Player.h"
#include "Test.h"
#include "Shader.h"
#include "Input.h"
#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class GameManager
{
public:
	GameManager();
	GameManager(GLint bufferWidth, GLint bufferHeight, GLFWwindow* mainWindow);

	void Update();
	void CreateShaders();
	void ClearHeap();

	Input* inputManager;

	~GameManager();
private:

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	Player* player = new Player(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	Test* test = new Test(glm::vec3(1.0f, 0.5f, -2.5f), 270.0f);

	glm::mat4 inputModel, outputModel, projection;
	std::vector<GameObject*> _gameObjList;
	std::vector<Shader> shaderList;

	GLfloat deltaTime = 0.0f;
	GLfloat lastTime = 0.0f;

	bool* keys;
};