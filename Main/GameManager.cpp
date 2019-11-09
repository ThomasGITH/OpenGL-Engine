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
	_gameObjList.push_back(otherTest);
	_gameObjList.push_back(sun);
	_gameObjList.push_back(lantern);

	_gameObjList.push_back(platform);

	_gameObjList.push_back(otherLantern);
	_gameObjList.push_back(mySpotLight);
	_gameObjList.push_back(flashLight);
	_gameObjList.push_back(dragon);

	inputManager = new Input(mainWindow);

	CompileIndividualLights();
	CreateShaders();
	projection = glm::perspective(70.0f, (GLfloat)bufferWidth / bufferHeight, 0.1f, 100.0f);
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
	uniformDLColour = shaderList[0].GetDLAmbientColourLocation();
	uniformDLAmbientIntensity = shaderList[0].GetDLAmbientIntensityLocation();
	uniformDLDirection = shaderList[0].GetDLDirectionLocation();
	uniformDLDiffuseIntensity = shaderList[0].GetDLDiffuseIntensityLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShinyness = shaderList[0].GetShinynessLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();

	for (size_t i = 0; i < _pointLightList.size(); i++)
	{
		GLuint PL_Colour = shaderList[0].getPointLightUniforms()[i].uniformColour;
		GLuint PL_ambientIntensity = shaderList[0].getPointLightUniforms()[i].uniformAmbientIntensity;
		GLuint PL_diffuseIntensity = shaderList[0].getPointLightUniforms()[i].uniformDiffuseIntensity;
		GLuint PL_position = shaderList[0].getPointLightUniforms()[i].uniformPosition;
		GLuint PL_constant = shaderList[0].getPointLightUniforms()[i].uniformConstant;
		GLuint PL_linear = shaderList[0].getPointLightUniforms()[i].uniformLinear;
		GLuint PL_quadrant = shaderList[0].getPointLightUniforms()[i].uniformQuadrant;

		_pointLightList[i]->setPointLightUniforms(PL_Colour, PL_ambientIntensity, PL_diffuseIntensity,
			PL_position, PL_constant, PL_linear, PL_quadrant);
	}

	for (size_t i = 0; i < _spotLightList.size(); i++)
	{
		GLuint SL_Colour = shaderList[0].getSpotLightUniforms()[i].uniformColour;
		GLuint SL_ambientIntensity = shaderList[0].getSpotLightUniforms()[i].uniformAmbientIntensity;
		GLuint SL_diffuseIntensity = shaderList[0].getSpotLightUniforms()[i].uniformDiffuseIntensity;
		GLuint SL_position = shaderList[0].getSpotLightUniforms()[i].uniformPosition;
		GLuint SL_constant = shaderList[0].getSpotLightUniforms()[i].uniformConstant;
		GLuint SL_linear = shaderList[0].getSpotLightUniforms()[i].uniformLinear;
		GLuint SL_quadrant = shaderList[0].getSpotLightUniforms()[i].uniformQuadrant;
		GLuint SL_edge = shaderList[0].getSpotLightUniforms()[i].uniformEdge;
		GLuint SL_direction = shaderList[0].getSpotLightUniforms()[i].uniformDirection;
				
		_spotLightList[i]->setSpotLightUniforms(SL_Colour, SL_ambientIntensity, SL_diffuseIntensity,
			SL_position, SL_constant, SL_linear, SL_quadrant, SL_edge, SL_direction);
	}

	// UPDATE ALL THE GAME OBJECTS:
	if (_gameObjList.size() > 0)
	{
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(player->getViewMatrix()));
		glUniform3f(uniformEyePosition, player->position.x, player->position.y, player->position.z);
		glUniform1i(shaderList[0].GetPointLightCountLocation(), _pointLightList.size());
		glUniform1i(shaderList[0].GetSpotLightCountLocation(), _spotLightList.size());

		for (size_t i = 0; i < _gameObjList.size(); i++)
		{
			_gameObjList[i]->Update(inputManager->getKeys(), deltaTime);
			_gameObjList[i]->Transform(model);
			_gameObjList[i]->calculateMouseMovement(inputManager->getXchange(), inputManager->getYchange());
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			_gameObjList[i]->renderModel();
			_gameObjList[i]->setUniformLocations(uniformDLColour, uniformDLAmbientIntensity, uniformDLDirection, uniformDLDiffuseIntensity, uniformSpecularIntensity, uniformShinyness);
			model = glm::mat4();
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

void GameManager::CompileIndividualLights()
{
	for (size_t i = 0; i < _gameObjList.size(); i++)
	{
		if (_gameObjList[i]->isPointLight)
		{
			_pointLightList.push_back(_gameObjList[i]);
		}
		else if (_gameObjList[i]->isSpotLight)
		{
			_spotLightList.push_back(_gameObjList[i]);
		}
	}
}

void GameManager::ClearHeap()
{
	std::cout << "CLEARING HEAP" << std::endl;
	for (unsigned int i = 0; i < _gameObjList.size(); i++)
	{
		delete _gameObjList[i];
	}

	//delete &_gameObjList;
		
	//delete &shaderList[0];
	
	delete inputManager;

}

GameManager::~GameManager()
{
	ClearHeap();
}
