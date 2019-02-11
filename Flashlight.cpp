#include "Flashlight.h"
#include "Locator.h"

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

	tag = "flashlight";
}

void FlashLight::Update(const bool* keys, const GLfloat& deltaTime)
{
	GameObject& player = Locator::FindObjectByTag("player");

	std::vector<GameObject*>& list = Locator::GetGameObjectList();

	if (keys[GLFW_KEY_3])
	{
		//Locator::GetGameObjectList().erase(list.begin() + 3);
		Locator::RemoveGameObject(2);
	}
	
	glm::vec3 playerPos = player.position;
	playerPos.y -= 0.3f;
	
	LightPosition = playerPos;
	direction = player.front;
	
	useLight(getUniformLocation(SPOT_COLOUR), getUniformLocation(SPOT_AMBIENT_INTENSITY), getUniformLocation(SPOT_DIRECTION),
		getUniformLocation(SPOT_DIFFUSE_INTENSITY), getUniformLocation(SPOT_POSITION), getUniformLocation(SPOT_CONSTANT),
		getUniformLocation(SPOT_LINEAR), getUniformLocation(SPOT_QUADRATIC), getUniformLocation(SPOT_EDGE));
}

FlashLight::~FlashLight()
{
}
