#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"

class GameObject
{
public:
	GameObject();

	glm::vec3 position;

	void Render(GLuint shaderID);
	void Update();

	~GameObject();
private:
	Mesh* mesh;
	Texture* texture;

	glm::mat4 model;
};