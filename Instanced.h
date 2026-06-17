#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

class Instanced
{
public:
	Instanced();

	void CreateMesh(GLfloat* vertices, GLuint verticesCount, GLuint* indices, GLuint indicesCount);
	void CreateInstanced(glm::vec3* vectors, size_t size);
	void Transform(glm::vec3 position);
	void Render(GLuint shaderID);

	~Instanced();
private:
	GLuint VAO, VBO, IBO, instancedVBO;
	GLuint count;

	glm::vec3* transform;
	size_t transform_size;

	glm::mat4 model;
	glm::vec3 position;
};

