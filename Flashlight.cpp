#include "Flashlight.h"
#include "Locator.h";

FlashLight::FlashLight(glm::vec3 position, glm::vec3 color, GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	this->position = position;
	LightPosition = position;
	this->colour = color;

	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;

	direction = glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f));

	edge = 20.0f;
	procEdge = cosf(glm::radians(edge));

	diffuseIntensity = 0.5f;
	ambientIntensity = 0.5f;

	isSpotLight = true;
	setLightType(SPOT);
}

glm::mat4 FlashLight::Update(glm::mat4 model, bool * keys, GLfloat deltaTime)
{
	std::vector<GameObject*> list = Locator::GetGameObjectList();
	/*
	glm::vec3 playerPos, playerDir;

	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i]->enableMouseCameraCalculations)
		{
			playerPos = list[i]->position;
			playerDir = list[i]->front;
			std::cout << i << std::endl;
		}
	}

	playerPos.y -= 0.3f;
	LightPosition = playerPos;
	direction = playerDir;
	*/
	LightPosition = position;

	useLight(getUniformLocation(SPOT_COLOUR), getUniformLocation(SPOT_AMBIENT_INTENSITY), getUniformLocation(SPOT_DIRECTION),
		getUniformLocation(SPOT_DIFFUSE_INTENSITY), getUniformLocation(SPOT_POSITION), getUniformLocation(SPOT_CONSTANT),
		getUniformLocation(SPOT_LINEAR), getUniformLocation(SPOT_QUADRATIC), getUniformLocation(SPOT_EDGE));

	return Transform(model, position, scale, rotation);
}

FlashLight::~FlashLight()
{
}
