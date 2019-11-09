#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "GameManager.h"

GLFWwindow* mainWindow;
GLint width = 1920, height = 1080, bufferWidth, bufferHeight;

//oldWidth = 1366, oldHeight = 768

int main()
{
	if (!glfwInit())
	{
		printf("Error initialising GLFW");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

	mainWindow = glfwCreateWindow(width, height, "Linssen Engine", glfwGetPrimaryMonitor(), NULL);
	if (!mainWindow)
	{
		printf("Error creating window");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);
	
	glewExperimental = GL_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		printf("Error: %s", glewGetErrorString(error));
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	GameManager gameManager(bufferWidth, bufferHeight, mainWindow);

	while (!gameManager.inputManager->getShouldClose())
	{
		glfwPollEvents();

		glClearColor(0.0f, 0.0f, 0.85f, 1.0f);
		//Color buffer: Stores all fragment colors/visual output
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		gameManager.Update();

		glfwSwapBuffers(mainWindow);
	}
	
	glfwTerminate();

	return 0;
}
