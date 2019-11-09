#include "Material.h"

Material::Material()
{
	setMaterialType(DEFAULT);
}

void Material::setMaterialType(GLfloat specularIntensity, GLfloat shinyness)
{
	this->specularIntensity = specularIntensity;
	this->shinyness = shinyness;
}

void Material::setMaterialType(Surface type)
{
	switch (type)
	{
	case DEFAULT: specularIntensity = 2.0f; shinyness = 32.0f; break;
	case DULL: specularIntensity = 0.3f; shinyness = 4.0f; break;
	case SHINY: specularIntensity = 4.0f; shinyness = 256.0f; break;
	default:  break;
	}
}

void Material::useMaterial(GLuint uniformSpecularIntensity, GLuint uniformShinyness)
{
	glUniform1f(uniformSpecularIntensity, specularIntensity);
	glUniform1f(uniformShinyness, shinyness);
}

Material::~Material()
{
	specularIntensity = 0;
	shinyness = 0;
}
