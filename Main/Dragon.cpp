#include "Dragon.h"

Dragon::Dragon(glm::vec3 position)
{
	this->position = position;
	
	position = glm::vec3(0,0,0);
	scale = glm::vec3(0.04f,0.04f,0.04f);
	setMaterialType(DULL);
	rotation.x -= 90;
}

void Dragon::Update(const bool* keys, const GLfloat& deltaTime)
{	
	//rotation.y += 0.2f;
	
	if (keys[GLFW_KEY_T])
	{
		position += right * 3.0f * deltaTime;
	}

	useMaterial(getUniformLocation(SPECULAR_INTENSITY), getUniformLocation(SPECULAR_SHINYNESS));
}

Dragon::~Dragon()
{

}
