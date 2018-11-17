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

	void useLight(GLuint uniformColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseIntensity,
		GLuint uniformPosition, GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant, GLuint uniformEdge);

	glm::vec3 colour, direction;
	GLfloat ambientIntensity, diffuseIntensity;

	LightType lightType;

	glm::vec3 LightPosition;
	GLfloat constant, linear, quadratic, edge, procEdge;

	~Light();
private:
};

