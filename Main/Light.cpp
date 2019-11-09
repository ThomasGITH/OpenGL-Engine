#include "Light.h"

Light::Light()
{
	colour = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::vec3(0.0f, 0.0f, -1.0f);
	ambientIntensity = 0.0f;
	diffuseIntensity = 1.0f;

	LightPosition = glm::vec3(0,0,0);
	constant = 0.3f;
	linear = 0.2f;
	quadratic = 0.1f;
}

void Light::setLightType(LightType type)
{
	lightType = type;
}

void Light::useLight(GLuint uniformColourLocation, GLuint uniformAmbientIntensityLocation, GLuint uniformDirectionLocation, GLuint uniformDiffuseIntensityLocation, GLuint uniformPosition,
	GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant, GLuint uniformEdge)
{
	switch (lightType)
	{
	case DIRECTIONAL :
		glUniform3f(uniformColourLocation, colour.x, colour.y, colour.z);
		glUniform1f(uniformAmbientIntensityLocation, ambientIntensity);
		glUniform1f(uniformDiffuseIntensityLocation, diffuseIntensity);

		glUniform3f(uniformDirectionLocation, direction.x, direction.y, direction.z);
		break;
	case POINT :
		glUniform3f(uniformColourLocation, colour.x, colour.y, colour.z);
		glUniform1f(uniformAmbientIntensityLocation, ambientIntensity);
		glUniform1f(uniformDiffuseIntensityLocation, diffuseIntensity);

		glUniform3f(uniformPosition, LightPosition.x, LightPosition.y, LightPosition.z);
		glUniform1f(uniformConstant, constant);
		glUniform1f(uniformLinear, linear);
		glUniform1f(uniformQuadrant, quadratic);
		break;
	case SPOT :
		glUniform3f(uniformColourLocation, colour.x, colour.y, colour.z);
		glUniform1f(uniformAmbientIntensityLocation, ambientIntensity);
		glUniform1f(uniformDiffuseIntensityLocation, diffuseIntensity);

		glUniform3f(uniformPosition, LightPosition.x, LightPosition.y, LightPosition.z);
		glUniform3f(uniformDirectionLocation, direction.x, direction.y, direction.z);
		glUniform1f(uniformConstant, constant);
		glUniform1f(uniformLinear, linear);
		glUniform1f(uniformQuadrant, quadratic);

		glUniform1f(uniformEdge, procEdge);
		break;
	}

}

Light::~Light()
{
}
