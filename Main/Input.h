#pragma once
#include <GLFW\glfw3.h>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class Input
{
public:
	Input();
	Input(GLFWwindow* mainWindow);

	bool* getKeys() { /*std::cout << "GETKEYS: " << keys << std::endl;*/  return keys; }
	GLfloat getXchange() { GLfloat theChange = xChange;  xChange = 0.0f; return theChange; }
	GLfloat getYchange() { GLfloat theChange = yChange;  yChange = 0.0f; return theChange; }
	bool getShouldClose() { return glfwWindowShouldClose(window); }
	void createCallBacks();

	~Input();
private:
	GLFWwindow* window;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved = true;

	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

