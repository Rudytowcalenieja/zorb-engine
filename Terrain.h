#pragma once

#define STB_PERLIN_IMPLEMENTATION

#include <array>
#include "Shader.h"
#include "Chunk.h"
#include "stb_perlin.h"

static constexpr unsigned int MAX_CHUNKS = 16;

class Terrain
{
public:
	Terrain(unsigned int x, unsigned int y);

	void Render(GLuint shaderID);

	~Terrain();
private:
	//std::array<Chunk*, MAX_CHUNKS> chunks;
	Chunk** chunks;

	unsigned int sizeX, sizeY;
	int** height;
};