#include "Shader.h"


Shader::Shader()
{
	shaderID = 0;

	uniformModel = 0;
	uniformProjection = 0; 
	uniformView = 0;
}

void Shader::createFromFile(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();
	processShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::processShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.phong.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.phong.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.phong.diffuseIntensity");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformShinyness = glGetUniformLocation(shaderID, "material.shinyness");
	uniformEyePosition = glGetUniformLocation(shaderID, "EyePosition");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightsCount");
	uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightsCount");
	
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].phong.colour", i);
		uniformPointLightList[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].phong.ambientIntensity", i);
		uniformPointLightList[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].phong.diffuseIntensity", i);
		uniformPointLightList[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLightList[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLightList[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLightList[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].quadratic", i);
		uniformPointLightList[i].uniformQuadrant = glGetUniformLocation(shaderID, locBuff);
	}

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.phong.colour", i);
		uniformSpotLightList[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.phong.ambientIntensity", i);
		uniformSpotLightList[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.phong.diffuseIntensity", i);
		uniformSpotLightList[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.position", i);
		uniformSpotLightList[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.constant", i);
		uniformSpotLightList[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.linear", i);
		uniformSpotLightList[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].base.quadratic", i);
		uniformSpotLightList[i].uniformQuadrant = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].edge", i);
		uniformSpotLightList[i].uniformEdge = glGetUniformLocation(shaderID, locBuff);

		snprintf(locBuff, sizeof(locBuff), "spotLights[%d].direction", i);
		uniformSpotLightList[i].uniformDirection = glGetUniformLocation(shaderID, locBuff);
	}
}

void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

void Shader::useShader()
{
	glUseProgram(shaderID);
}

void Shader::clearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;
	uniformView = 0;
	uniformDirectionalLight.uniformColour = 0;
	uniformDirectionalLight.uniformAmbientIntensity = 0;
	uniformDirectionalLight.uniformDirection = 0;
	uniformDirectionalLight.uniformDiffuseIntensity = 0;
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::GetModelLocation()
{
	return uniformModel;
}
GLuint Shader::GetViewLocation()
{
	return uniformView;
}

GLuint Shader::GetDLAmbientColourLocation()
{
	return uniformDirectionalLight.uniformColour;
}

GLuint Shader::GetDLAmbientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetDLDirectionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetDLDiffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShinynessLocation()
{
	return uniformShinyness;
}

GLuint Shader::GetEyePositionLocation()
{
	return uniformEyePosition;
}

GLuint Shader::GetPointLightCountLocation()
{
	return uniformPointLightCount;
}

GLuint Shader::GetSpotLightCountLocation()
{
	return uniformSpotLightCount;
}

Shader::~Shader()
{
	clearShader();
}
