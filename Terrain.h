#pragma once

#include "Shader.h"

class Terrain
{
public:
	Terrain(unsigned int x, unsigned int y);

	void Render(GLuint shaderID);

	~Terrain();
private:
	unsigned int sizeX, sizeY;
	int** height;
};