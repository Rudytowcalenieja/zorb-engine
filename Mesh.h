#pragma once

#include <iostream>

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();

	void Create(GLfloat *vertices, GLuint verticesCount, GLuint *indices, GLuint indicesCount);

	void Render();

	~Mesh();
private:
	GLuint VAO, VBO, IBO;

	GLuint count;
};