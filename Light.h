#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

#include "Mesh.h"
#include "Shader.h"

class Light
{
public:
	Light(glm::vec3 ambient, glm::vec3 pos);

	void Render(GLuint shaderID);

	~Light();
private:
	glm::vec3 color;
	glm::vec3 position;

	GLuint VAO;
	GLuint VBO;

	Mesh* mesh;
};

