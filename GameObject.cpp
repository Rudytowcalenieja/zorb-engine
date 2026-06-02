#include "GameObject.h"

GLfloat cubeVertices[] = {
    // Front (+Z)
    -0.5f,-0.5f, 0.5f,   0,0,1,  0,0,
     0.5f,-0.5f, 0.5f,   0,0,1,  1,0,
     0.5f, 0.5f, 0.5f,   0,0,1,  1,1,
    -0.5f, 0.5f, 0.5f,   0,0,1,  0,1,

    // Back (�Z)
    -0.5f,-0.5f,-0.5f,   0,0,-1, 1,0,
     0.5f,-0.5f,-0.5f,   0,0,-1, 0,0,
     0.5f, 0.5f,-0.5f,   0,0,-1, 0,1,
    -0.5f, 0.5f,-0.5f,   0,0,-1, 1,1,

    // Left (�X)
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

     // Bottom (�Y)
     -0.5f,-0.5f,-0.5f,   0,-1,0, 0,0,
      0.5f,-0.5f,-0.5f,   0,-1,0, 1,0,
      0.5f,-0.5f, 0.5f,   0,-1,0, 1,1,
     -0.5f,-0.5f, 0.5f,   0,-1,0, 0,1
};

GLuint cubeIndices[] = {
     0, 1, 2,  2, 3, 0,   // Front
     4, 5, 6,  6, 7, 4,   // Back
     8, 9,10, 10,11, 8,   // Left
    12,13,14, 14,15,12,   // Right
    16,17,18, 18,19,16,   // Top
    20,21,22, 22,23,20    // Bottom
};

GameObject::GameObject() {
  mesh = new Mesh();
  mesh->Create(cubeVertices, 192, cubeIndices, 36);

   model = glm::mat4(1.0f);

  texture = new Texture("Textures/dirt.png");
}

void GameObject::Render(GLuint shaderID) {
Shader::SetMatrix4(shaderID, "model", model);
texture->Use();
mesh->Render();
}

void GameObject::Update() {model = glm::translate(glm::mat4(1.0f), position);
}

GameObject::~GameObject() {
mesh->~Mesh();
}