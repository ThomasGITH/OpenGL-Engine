#include "GameObject.h"
#include <iostream>
#include <glm\glm.hpp>
#include "Locator.h"

GameObject::GameObject()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

	scale.x = 0.04f;
	scale.y = 0.04f;
	scale.z = 0.04f;

	enableMouseCameraCalculations = false;
	invertMouse = false;
	disableCameraClamp = false;
	isPointLight = false;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	textureID = 0;
	textureWidth = 0;
	textureHeight = 0;
	textureBitDepth = 0;
	textureLocation = 0;

	moveSpeed = 2.5f;

	front = glm::vec3(0.0f, 0.0f, 1.0f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	tag = "";
}

void GameObject::loadModel(const std::string &fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
	
	if (!scene)
	{
		printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
		return;
	}

	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);
}

void GameObject::LoadNode(aiNode* node, const aiScene* scene)
{
	//Loops through the meshlist of the corresponding node
	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		//The node only stores the ID of the mesh, the scene itself stores the mesh.
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	//Loops through the meshlist of this node's child-nodes
	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}
}

void GameObject::LoadMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	//1 Face = 3 indices die dan dus samen een "face" maken
	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();
	newMesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size(), false);
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void GameObject::LoadMaterials(const aiScene* scene)
{
	textureList.resize(scene->mNumMaterials);
	
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial* material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			std::cout << "textureTest" << std::endl;

			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx + 1);
				
				std::string texPath = std::string("Textures/" + filename);

				textureList[i] = new Texture(texPath.c_str());

				if (!textureList[i]->LoadTexture())
				{
					printf("Failed to load texture at: %s\n", texPath);
					delete textureList[i];
					textureList[i] = nullptr;
				}
			}
		}

		if (!textureList[i])
		{
			textureList[i] = new Texture("Textures/not_found.png");
			textureList[i]->LoadTexture();
		}
	}
}

void GameObject::createMeshFromScratch(GLfloat * vertices, char* textureLocation, unsigned int * indices, unsigned int numOfVertices, unsigned int numOfIndices, bool useAlphaTexture, bool calculateNormals)
{
	Mesh* mesh = new Mesh();
	Texture* tex = new Texture(textureLocation);
	mesh->createMesh(vertices, indices, numOfVertices, numOfIndices, calculateNormals);

	if (useAlphaTexture)
	{
		tex->LoadTextureA();
	}
	else 
	{
		tex->LoadTexture();
	}

	rawMesh.push_back(mesh);
	rawTexture.push_back(tex);
}

void GameObject::renderModel()
{
	if (rawMesh.size() > 0)
	{
		rawTexture[0]->RenderTexture();
		rawMesh[0]->renderMesh();
	}
	else if (meshList.size() > 0)
	{
		for (size_t i = 0; i < meshList.size(); i++)
		{
			unsigned int materialIndex = meshToTex[i];

			if (materialIndex < textureList.size() && textureList[materialIndex])
			{
				textureList[materialIndex]->RenderTexture();
			}

			meshList[i]->renderMesh();
		}
	}
}

void GameObject::Transform(glm::mat4& model)
{
	model = glm::translate(model, position);

	if (!enableMouseCameraCalculations) {
		if (rotation.y < 0) { rotation.y += 360; } else if (rotation.y > 360) { rotation.y -= 360; }
		if (rotation.x < 0) { rotation.x += 360; } else if (rotation.x > 360) { rotation.x -= 360; }
		if (rotation.z < 0) { rotation.z += 360; } else if (rotation.z > 360) { rotation.z -= 360; }
	}
	
	glm::mat4 rotationMatrix = glm::toMat4(glm::quat(glm::radians(rotation)));

	model *= rotationMatrix;
	model = glm::scale(model, scale);
}

void GameObject::calculateMouseMovement(GLfloat mouseXChange, GLfloat mouseYChange)
{
	if (enableMouseCameraCalculations)
	{
		mouseXChange *= turnSpeed;
		mouseYChange *= turnSpeed;
		
		rotation.x += mouseXChange;
		rotation.y += mouseYChange;

		rotation.y = disableCameraClamp ? rotation.y : glm::clamp(rotation.y, -89.0f, 89.0f);
	}

	//Calculate the front, right and up vectors (very important)
	front.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	front.y = sin(glm::radians(rotation.y));
	front.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
	front = glm::normalize(front);
	
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

	front.y = invertMouse ? front.y * -1 : front.y;
}

glm::mat4 GameObject::getViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void GameObject::setUniformLocations(GLuint uniformAmbientColour, GLuint uniformAmbientIntensity, GLuint uniformDirection, GLuint uniformDiffuseIntensity, GLuint uniformSpecularIntensity, GLuint uniformShinyness)
{
	this->uniformColour = uniformAmbientColour;
	this->uniformAmbientIntensity = uniformAmbientIntensity;
	this->uniformDirection = uniformDirection;
	this->uniformDiffuseIntensity = uniformDiffuseIntensity;
	this->uniformSpecularIntensity = uniformSpecularIntensity;
	this->uniformShinyness = uniformShinyness;
}

void GameObject::setPointLightUniforms(GLuint uniformColour, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity, GLuint uniformPosition, GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant)
{
	pointLight.uniformColour = uniformColour;
	pointLight.uniformAmbientIntensity = uniformAmbientIntensity;
	pointLight.uniformDiffuseIntensity = uniformDiffuseIntensity;
	pointLight.uniformPosition = uniformPosition;
	pointLight.uniformConstant = uniformConstant;
	pointLight.uniformLinear = uniformLinear;
	pointLight.uniformQuadrant = uniformQuadrant;
}

void GameObject::setSpotLightUniforms(GLuint uniformColour, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity, GLuint uniformPosition, GLuint uniformConstant, GLuint uniformLinear, GLuint uniformQuadrant, GLuint uniformEdge, GLuint uniformDirection)
{
	spotLight.uniformColour = uniformColour;
	spotLight.uniformAmbientIntensity = uniformAmbientIntensity;
	spotLight.uniformDiffuseIntensity = uniformDiffuseIntensity;
	spotLight.uniformPosition = uniformPosition;
	spotLight.uniformConstant = uniformConstant;
	spotLight.uniformLinear = uniformLinear;
	spotLight.uniformQuadrant = uniformQuadrant;
	spotLight.uniformEdge = uniformEdge;
	spotLight.uniformDirection = uniformDirection;
}

GLuint GameObject::getUniformLocation(uniform location)
{
	switch (location)
	{
	case DL_COLOUR: return uniformColour; break;
	case DL_AMBIENT_INTENSITY: return uniformAmbientIntensity; break;
	case DL_DIRECTION: return uniformDirection; break;
	case DL_DIFFUSE_INTENSITY: return uniformDiffuseIntensity; break;

	case SPECULAR_INTENSITY: return uniformSpecularIntensity; break;
	case SPECULAR_SHINYNESS: return uniformShinyness; break;

	case POINT_COLOUR: return pointLight.uniformColour; break;
	case POINT_AMBIENT_INTENSITY: return pointLight.uniformAmbientIntensity; break;
	case POINT_DIFFUSE_INTENSITY: return pointLight.uniformDiffuseIntensity; break;
	case POINT_POSITION: return pointLight.uniformPosition; break;
	case POINT_CONSTANT: return pointLight.uniformConstant; break;
	case POINT_LINEAR: return pointLight.uniformLinear; break;
	case POINT_QUADRATIC: return pointLight.uniformQuadrant; break;

	case SPOT_COLOUR: return spotLight.uniformColour; break;
	case SPOT_AMBIENT_INTENSITY: return spotLight.uniformAmbientIntensity; break;
	case SPOT_DIFFUSE_INTENSITY: return spotLight.uniformDiffuseIntensity; break;
	case SPOT_POSITION: return spotLight.uniformPosition; break;
	case SPOT_CONSTANT: return spotLight.uniformConstant; break;
	case SPOT_LINEAR: return spotLight.uniformLinear; break;
	case SPOT_QUADRATIC: return spotLight.uniformQuadrant; break;
	case SPOT_EDGE: return spotLight.uniformEdge; break;
	case SPOT_DIRECTION: return spotLight.uniformDirection; break;
	default: break;
	}
}

void GameObject::clearModel()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	textureWidth = 0;
	textureHeight = 0;
	textureBitDepth = 0;
	textureLocation = 0;

	indexCount = 0;

	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}

	if (!rawMesh.empty())
	{
		delete rawMesh[0];
		rawMesh[0] = nullptr;
	}

	if (!rawTexture.empty())
	{
		delete rawTexture[0];
		rawTexture[0] = nullptr;
	}
}

GameObject::~GameObject()
{
	clearModel();
}
