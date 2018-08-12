#include "GameManager.h"
#include "Locator.h"
#include <iostream>
#include <cmath>
#include <GLFW\glfw3.h>
#include <string.h>
#include <glm\glm.hpp>

static const char* vShader = "Shaders/shader.vert";
static const char* fShader = "Shaders/shader.frag";

GameManager::GameManager(GLint bufferWidth, GLint bufferHeight, GLFWwindow* mainWindow)
{
	Locator::setGameManagerReference(this);

	_gameObjList.push_back(player);
	_gameObjList.push_back(test);
	_gameObjList.push_back(sun);
	
	inputManager = new Input(mainWindow);

	CreateShaders();

	projection = glm::perspective(45.0f, (GLfloat)bufferWidth / bufferHeight, 0.1f, 100.0f);
}


void GameManager::Update()
{
	GLfloat now = glfwGetTime();
	deltaTime = now - lastTime;
	lastTime = now;
	
	shaderList[0].useShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
	uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
	uniformDirection = shaderList[0].GetDirectionLocation();
	uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();

	// UPDATE ALL THE GAME OBJECTS:
	if (_gameObjList.size() > 0)
	{
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(player->getViewMatrix()));
		for (unsigned int i = 0; i < _gameObjList.size(); i++)
		{
			outputModel = _gameObjList[i]->Update(inputModel, inputManager->getKeys(), deltaTime);
			_gameObjList[i]->calculateMouseMovement(inputManager->getXchange(), inputManager->getYchange());
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(outputModel));
			_gameObjList[i]->renderModel();
			_gameObjList[i]->setUniformLocations(uniformAmbientColour, uniformAmbientIntensity, uniformDirection, uniformDiffuseIntensity);
			outputModel = glm::mat4();
		}
	}

	glUseProgram(0);
}

void GameManager::CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->createFromFile(vShader, fShader);
	shaderList.push_back(*shader1);
}

void GameManager::ClearHeap()
{
	std::cout << "CLEARING HEAP" << std::endl;
	for (unsigned int i = 0; i < _gameObjList.size(); i++)
	{
		delete _gameObjList[i];
	}
}

GameManager::~GameManager()
{
	ClearHeap();
}