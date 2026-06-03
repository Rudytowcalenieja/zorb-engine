#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

// TODO: create instanced rendering
class Instanced
{
public:
	Instanced();

	void CreateMesh(GLfloat* vertices, GLuint verticesCount, GLuint* indices, GLuint indicesCount);
	void CreateInstanced(glm::vec3* vectors, size_t size);
	void Render(GLuint shaderID);

	~Instanced();
private:
	GLuint VAO, VBO, IBO, instancedVBO;
	GLuint count;

	glm::vec3* transform;
	size_t transform_size;

	glm::mat4 model;
};

