#include "Light.h"

Light::Light()
{
}

void Light::setLightType(LightType type)
{
	lightType = type;
}

void Light::useLight(GLuint uniformAmbientColourLocation, GLuint uniformAmbientIntensityLocation, GLuint uniformDirectionLocation, GLuint uniformDiffuseIntensityLocation)
{
	if (lightType == DIRECTIONAL)
	{
		glUniform3f(uniformAmbientColourLocation, colour.x, colour.y, colour.z);
		glUniform1f(uniformAmbientIntensityLocation, ambientIntensity);

		glUniform3f(uniformDirectionLocation, direction.x, direction.y, direction.z);
		glUniform1f(uniformDiffuseIntensityLocation, diffuseIntensity);
	}
	else 
	{
		std::cout << "No LightType selected" << std::endl;
	}
}

Light::~Light()
{
}
