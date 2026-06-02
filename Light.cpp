#include "Light.h"

GLfloat lightVertices[] = {
    // Front (+Z)
    -0.5f,-0.5f, 0.5f,   0,0,1,  0,0,
     0.5f,-0.5f, 0.5f,   0,0,1,  1,0,
     0.5f, 0.5f, 0.5f,   0,0,1,  1,1,
    -0.5f, 0.5f, 0.5f,   0,0,1,  0,1,

    // Back (–Z)
    -0.5f,-0.5f,-0.5f,   0,0,-1, 1,0,
     0.5f,-0.5f,-0.5f,   0,0,-1, 0,0,
     0.5f, 0.5f,-0.5f,   0,0,-1, 0,1,
    -0.5f, 0.5f,-0.5f,   0,0,-1, 1,1,

    // Left (–X)
    -0.5f,-0.5f,-0.5f,  -1,0,0,  0,0,
    -0.5f, 0.5f,-0.5f,  -1,0,0,  1,0,
    -0.5f, 0.5f, 0.5f,  -1,0,0,  1,1,
    -0.5f,-0.5f, 0.5f,  -1,0,0,  0,1,

    // Right (+X)
     0.5f,-0.5f,-0.5f,   1,0,0,  0,0,
     0.5f, 0.5f,-0.5f,   1,0,0,  1,0,
     0.5f, 0.5f, 0.5f,   1,0,0,  1,1,
     0.5f,-0.5f, 0.5f,   1,0,0,  0,1,

     // Top (+Y)
     -0.5f, 0.5f,-0.5f,   0,1,0,  0,0,
      0.5f, 0.5f,-0.5f,   0,1,0,  1,0,
      0.5f, 0.5f, 0.5f,   0,1,0,  1,1,
     -0.5f, 0.5f, 0.5f,   0,1,0,  0,1,

     // Bottom (–Y)
     -0.5f,-0.5f,-0.5f,   0,-1,0, 0,0,
      0.5f,-0.5f,-0.5f,   0,-1,0, 1,0,
      0.5f,-0.5f, 0.5f,   0,-1,0, 1,1,
     -0.5f,-0.5f, 0.5f,   0,-1,0, 0,1
};

GLuint lightIndices[] = {
     0, 1, 2,  2, 3, 0,   // Front
     4, 5, 6,  6, 7, 4,   // Back
     8, 9,10, 10,11, 8,   // Left
    12,13,14, 14,15,12,   // Right
    16,17,18, 18,19,16,   // Top
    20,21,22, 22,23,20    // Bottom
};

Light::Light(glm::vec3 ambient, glm::vec3 pos) : color(ambient), position(pos) { // To test
	VAO = 0;
	VBO = 0;

	mesh = new Mesh();
	mesh->Create(lightVertices, 192, lightIndices, 36);
}

void Light::Render(GLuint shaderID) {
	Shader::SetVec3(shaderID, "lightColor", color);

	mesh->Render();
}