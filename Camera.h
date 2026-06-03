#pragma once

#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();

	void HandleKeys(GLFWwindow* window, float deltaTime);
	void HandleMouse(GLFWwindow* window, float deltaTime);

	glm::mat4& GetView() { return view; }
	glm::vec3& GetPos() { return position; }

	~Camera();
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 direction;

	glm::vec3 worldUp;
	glm::vec3 camFront;
	glm::vec3 camRight;
	glm::vec3 camUp;

	glm::mat4 view;

	glm::vec3 lookDir;

	float yaw, pitch;

	bool firstMouse;
	float lastX, lastY;

	double mouseX, mouseY;
};

