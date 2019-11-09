#pragma once
#include <GL\glew.h>

class Material
{
public:
	enum Surface { SHINY, DULL, DEFAULT};
	Material();

	void setMaterialType(GLfloat specularIntensity, GLfloat shinyness);
	void setMaterialType(Surface shinyness);
	void useMaterial(GLuint uniformSpecularIntensity, GLuint uniformShinyness);

	~Material();
private:
	GLfloat specularIntensity, shinyness;
};

