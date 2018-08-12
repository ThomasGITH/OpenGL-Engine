#pragma once
#include <iostream>
#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light();

	enum LightType { DIRECTIONAL, POINT, SPOT };
	void setLightType(LightType type);

	void useLight(GLuint uniformAmbientColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseIntensity);

	glm::vec3 colour, direction;
	GLfloat ambientIntensity, diffuseIntensity;
	
	LightType lightType;

	~Light();
private:
};

