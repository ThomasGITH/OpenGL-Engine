#include <iostream>
#include <vector>
#include <stdio.h>
#include <glm\glm.hpp>
#include "Player.h"
#include "Shader.h"
#include "GameObject.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class GameManager
{
public:
	GameManager();
	GameManager(GLint bufferWidth, GLint bufferHeight);

	void Update();
	void CreateShaders();

	~GameManager();
private:

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	Player* player;

	glm::mat4 inputModel, outputModel, projection;
	std::vector<GameObject*> _gameObjList;
	std::vector<Shader> shaderList;
};