#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include "stb_image.h"
#include <vector>
#include<glm\gtc\quaternion.hpp>
#include <glm\gtx\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>

class Locator;

class GameObject
{
public:
	GameObject();

	virtual glm::mat4 Update(glm::mat4 model, bool* keys, GLfloat deltaTime) = 0;
	void setUniformLocations(GLuint uniformAmbientColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseLocation, GLuint uniformSpecularLocation, GLuint uniformShinyness);
	void setPointLightUniforms(GLuint uniformColour, GLuint uniformAmbientIntensity,GLuint uniformDiffuseIntensity,GLuint uniformPosition,
	GLuint uniformConstant, GLuint uniformLinear,GLuint uniformQuadrant);
	void setSpotLightUniforms(GLuint uniformColour, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity, GLuint uniformPosition,
		GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant, GLuint uniformEdge, GLuint uniformDirection);

	glm::mat4 getViewMatrix();
	enum uniform {DL_COLOUR, DL_AMBIENT_INTENSITY, DL_DIRECTION, DL_DIFFUSE_INTENSITY, SPECULAR_INTENSITY, SPECULAR_SHINYNESS,
	POINT_COLOUR, POINT_AMBIENT_INTENSITY, POINT_DIFFUSE_INTENSITY, POINT_POSITION, POINT_CONSTANT, POINT_LINEAR, POINT_QUADRATIC,
	SPOT_COLOUR, SPOT_AMBIENT_INTENSITY, SPOT_DIFFUSE_INTENSITY, SPOT_POSITION, SPOT_CONSTANT, SPOT_LINEAR, SPOT_QUADRATIC, SPOT_EDGE, SPOT_DIRECTION};
	GLuint getUniformLocation(uniform location);
	void calculateMouseMovement(GLfloat xChange, GLfloat yChange);

	void createModel(GLfloat *vertices, char* textureLocation, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices, bool calculateNormals);
	void renderModel();
	GLfloat* calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset);
	void clearModel();

	glm::mat4 Transform(glm::mat4 model, glm::vec3 position, glm::vec3 scale, glm::vec3 angleAxis);
	glm::vec3 position, rotation, scale, front, up, right, worldUp;
	GLfloat yaw, pitch, moveSpeed, turnSpeed, rotationAngle;

	bool enableMouseCameraCalculations, invertMouse, disableCameraClamp, isPointLight, isSpotLight;
	bool tester = false;

	struct PointLight
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformQuadrant;
	};

	PointLight pointLight;

	struct SpotLight
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformQuadrant;

		GLuint uniformEdge;
		GLuint uniformDirection;
	};

	SpotLight spotLight;

	~GameObject();
private:
	GLuint VAO, VBO, IBO, textureID;
	GLsizei indexCount;
	const float toRadians = 3.14159265f / 180.0f;
	char* textureLocation;


	int textureWidth, textureHeight, textureBitDepth;
	GLuint uniformColour, uniformAmbientIntensity, uniformDirection, uniformDiffuseIntensity, uniformSpecularIntensity, uniformShinyness;
};
