#include "Input.h"


Input::Input()
{

}

Input::Input(GLFWwindow* mainWindow)
{

	glfwSetWindowUserPointer(mainWindow, this);

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow,handleMouse);

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	window = mainWindow;
}

void Input::createCallBacks()
{
}

void Input::handleKeys(GLFWwindow * window, int key, int code, int action, int mode)
{
	Input* theWindow = static_cast<Input*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}

}

void Input::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Input* theWindow = static_cast<Input*>(glfwGetWindowUserPointer(window));


	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

Input::~Input()
{
}
