#pragma once

#include <array>
#include <unordered_map>

#include "stb_perlin.h"
#include "Chunk.h"
#include "Frustum.h"

static constexpr unsigned int MAX_CHUNKS = 16;

class Terrain
{
public:
	Terrain();

	void GenerateTerrain(unsigned int x, unsigned int y);

	void Render(GLuint shaderID, Frustum frustum);

	~Terrain();
private:
	std::unordered_map<unsigned int, Chunk*> chunks;

	unsigned int sizeX, sizeZ;
	int** height;
};