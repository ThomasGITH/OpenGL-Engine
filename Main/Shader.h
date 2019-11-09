#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Commons.h"

#include <GL\glew.h>

class Shader
{
public:
	Shader();

	void createFromFile(const char* vertexLocation, const char* fragmentLocation);
	std::string readFile(const char* fileLocation);
	void processShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	void useShader();
	void clearShader();
	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetDLAmbientColourLocation();
	GLuint GetDLAmbientIntensityLocation();
	GLuint GetDLDirectionLocation();
	GLuint GetDLDiffuseIntensityLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShinynessLocation();
	GLuint GetEyePositionLocation();
	GLuint GetPointLightCountLocation();
	GLuint GetSpotLightCountLocation();

	~Shader();
private:
	//shaderID and uniform locations
	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformSpecularIntensity, uniformShinyness, uniformEyePosition,
		uniformPointLightCount, uniformSpotLightCount;
	
	struct {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;
	
	//struct-array van pointLight locaties
	struct PointLight{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformQuadrant;
	} uniformPointLightList[MAX_POINT_LIGHTS];

	struct SpotLight {
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformQuadrant;

		GLuint uniformEdge;
		GLuint uniformDirection;
	} uniformSpotLightList[MAX_SPOT_LIGHTS];

public:
	PointLight* getPointLightUniforms() { return uniformPointLightList; }
	SpotLight* getSpotLightUniforms() { return uniformSpotLightList; }
};

