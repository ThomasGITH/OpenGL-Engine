#pragma once
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

class Mesh
{
public:
	Mesh();
	
	void createMesh(GLfloat * vertices, unsigned int * indices, unsigned int numOfVertices, unsigned int numOfIndices, bool calculateNormals);
	void renderMesh();
	void clearMesh();

	~Mesh();
private:

	GLfloat* calcAverageNormals(unsigned int * indices, unsigned int indiceCount, GLfloat * vertices, unsigned int verticeCount,
		unsigned int vLength, unsigned int normalOffset);

	GLuint VAO, VBO, IBO, textureID;
	GLsizei indexCount;
	char* textureLocation;
	int textureWidth, textureHeight, textureBitDepth;

};

