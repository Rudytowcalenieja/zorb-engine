#include "Camera.h"

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(position - target);

	worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	camFront = glm::vec3(0.0f, 0.0f, -1.0f);
	camRight = glm::normalize(glm::cross(worldUp, direction));
	camUp = glm::cross(direction, camRight);

	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
					   glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec3(0.0f, 1.0f, 0.0f));

	yaw = -90.0f;
	pitch = 0.0f;

	lastX = 600;
	lastY = 450;
}

void Camera::HandleKeys(GLFWwindow* window, float deltaTime) {
	//const float radius = 3.0f;
	//float camX = sin(glfwGetTime()) * radius;
	//float camZ = cos(glfwGetTime()) * radius;
	//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

	view = glm::lookAt(position, position + camFront, camUp);

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += cameraSpeed * camFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= cameraSpeed * camFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position += cameraSpeed * camUp;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		position -= cameraSpeed * camUp;
}

void Camera::HandleMouse(GLFWwindow* window, float deltaTime) {
	lookDir.x = cos(glm::radians(yaw)); // Note that we convert the angle to radians first
	lookDir.z = sin(glm::radians(yaw));

	lookDir.y = sin(glm::radians(pitch));

	glfwGetCursorPos(window, &mouseX, &mouseY);

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (firstMouse)
	{
		lastX = mouseX;
		lastY = mouseY;
		firstMouse = false;
	}

	float xoffset = mouseX - lastX;
	float yoffset = lastY - mouseY;
	lastX = mouseX;
	lastY = mouseY;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	lookDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	lookDir.y = sin(glm::radians(pitch));
	lookDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(lookDir);
}

Camera::~Camera() {

}