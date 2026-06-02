#include "Engine.h"

#include "Instanced.h"

const char* WINDOW_TITLE = "Simple Engine";
const int WINDOW_WIDTH = 1800;
const int WINDOW_HEIGHT = 1200;

const char* vertexPath = "Shaders/vertex.glsl";
const char* instancedPath = "Shaders/instanced.glsl";
const char* fragmentPath = "Shaders/fragment.glsl";
const char* lightPath = "Shaders/light.glsl";

// GLfloat vertices[]{
// 	-0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
// 	 0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
// 	-0.5f,  0.5f,  0.5f,   0.0f, 1.0f,
// 	 0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
// 	-0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
// 	 0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
// 	-0.5f,  0.5f, -0.5f,   0.0f, 1.0f,
// 	 0.5f,  0.5f, -0.5f,   1.0f, 1.0f
// };

GLfloat vertices[] = {

	// FRONT
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,

	// BACK
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,

	// LEFT
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

	// RIGHT
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

	// TOP
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,

	// BOTTOM
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f
};

GLuint indices[] = {
	0,  1,  2,   1,  3,  2,   // front
	4,  5,  6,   5,  7,  6,   // back
	8,  9, 10,   9, 11, 10,   // left
   12, 13, 14,  13, 15, 14,   // right
   16, 17, 18,  17, 19, 18,   // top
   20, 21, 22,  21, 23, 22    // bottom
};

Instanced instanced;

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	
}

Engine::Engine() {
	camera = Camera();
}

void Engine::CreateShaders() {
	Shader* mainShader = new Shader(vertexPath, fragmentPath);
	shaderList.push_back(mainShader);

	Shader* lightShader = new Shader(vertexPath, lightPath);
	shaderList.push_back(lightShader);

	Shader* instancedShader = new Shader(instancedPath, fragmentPath);
	shaderList.push_back(instancedShader);
}

void Engine::CreateMesh() {
	/*Mesh* cube = new Mesh();
	cube->Create(cubeVertices, 120, cubeIndices, 36);
	meshList.push_back(cube);
	meshList.push_back(cube);*/

	GameObject* object = new GameObject();
	gameObjectList.push_back(object);

	instanced.CreateMesh(vertices, 192, indices, 36);
}

void Engine::CreateTextures() {
	Texture box_diffuse("Textures/box.png");
	textureList.push_back(box_diffuse);

	Texture box_specular("Textures/box_specular.png");
	textureList.push_back(box_specular);
}

void Engine::CreateLights() {
	Light* light = new Light(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	lightList.push_back(light);
}

void Engine::Setup() {
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		printf("ERROR >> GLFW >> Cannot initialize!\n");
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window) {
		printf("ERROR >> WINDOW >> Cannot create window!\n");
		glfwTerminate();
		return;
	}
	printf("Using GLFW %s\n", glfwGetVersionString());

	// Set keyboard and mouse
	glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		printf("ERROR >> GLEW >> %s\n", glewGetErrorString(err));
	}
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));

	glfwSwapInterval(0);

	CreateShaders();
	CreateMesh();
	CreateTextures();
	CreateLights();

	glfwGetFramebufferSize(window, &width, &height);
	const float ratio = (float)width / (float)height;
	constexpr float fov = glm::radians(45.0f);

	projection = glm::perspective(fov, ratio, 0.1f, 100.0f);
	
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

	glEnable(GL_DEPTH_TEST);

	glm::vec3 transforms[25];
	for (int i = 0; i < 25; i++) {
		transforms[i] = glm::vec3(i % 5 * 1.0f, 0.0f, i / 5 * 1.0f);
	}

	instanced.CreateInstanced(transforms, 25);
}

void Engine::Render() {
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Window
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Camera
		camera.HandleKeys(window, deltaTime);
		camera.HandleMouse(window, deltaTime);

		// Rendering
		// shaderList[1]->use();
		// shaderList[1]->SetMatrix4("projection", projection);
		// shaderList[1]->SetMatrix4("view", camera.GetView());
		//
		// // Lights
		// model = glm::mat4(1.0f);
		// shaderList[1]->SetMatrix4("model", model);
		// // lightList[0]->Render(shaderList[1]->ID);
		//
		// // Objects
		// shaderList[0]->use();
		// shaderList[0]->SetVec3("lightPos", glm::vec3(2.0f, 2.0f, 0.0f));
		// shaderList[0]->SetVec3("lightColor", glm::vec3(0.0f, 1.0f, 0.0f));
		// shaderList[0]->SetMatrix4("projection", projection);
		// shaderList[0]->SetMatrix4("view", camera.GetView());

		// gameObjectList[0]->position = glm::vec3(1.0f, 0.0f, 1.0f);

		// for (GameObject* object : gameObjectList) {
		// 	object->Update();
		// 	object->Render(shaderList[0]->ID);
		// }

		shaderList[2]->use();
		shaderList[2]->SetVec3("lightPos", glm::vec3(2.0f, 2.0f, 0.0f));
		shaderList[2]->SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 0.0f));

		shaderList[2]->SetVec3("viewPos", camera.GetPos());

		shaderList[2]->SetVec3("light.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderList[2]->SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shaderList[2]->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		// shaderList[2]->SetVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		// shaderList[2]->SetVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		shaderList[2]->SetFloat("material.shininess", 64.0f);

		shaderList[2]->SetMatrix4("projection", projection);
		shaderList[2]->SetMatrix4("view", camera.GetView());

		shaderList[2]->SetInt("material.diffuse", textureList[0].GetID());
		textureList[0].Use();

		shaderList[2]->SetInt("material.specular", textureList[1].GetID());
		textureList[1].Use();

		instanced.Render(shaderList[2]->ID);

		glfwSwapBuffers(window);
		glfwPollEvents();
	};

}

Engine::~Engine() {
	glfwDestroyWindow(window);
	glfwTerminate();
}