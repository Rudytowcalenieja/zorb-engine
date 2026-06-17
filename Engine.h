#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "Instanced.h"
#include "Terrain.h"

class Engine
{
public:
	Engine();

	void CreateShaders();
	void CreateMesh();
	void CreateTextures();
	void CreateLights();
	void Setup();

	void Update();
	void Render();

	~Engine();

private:
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame

	std::vector<Shader*> shaderList;
	std::vector<Mesh*> meshList;
	std::vector<Light*> lightList;
	std::vector<GameObject*> gameObjectList;
	std::vector<Texture> textureList;

	/*GLuint VAO, VBO, IBO;*/

	GLFWwindow* window;
	int width, height;

	Camera camera;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

	Frustum frustum;
};

