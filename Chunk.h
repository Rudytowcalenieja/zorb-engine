#pragma once

#include <GL/glew.h>
#include <cstdint>
#include <array>
#include "Instanced.h"

using BlockID = uint8_t;

static constexpr unsigned int SIZE_X = 16;
static constexpr unsigned int SIZE_Y = 256;
static constexpr unsigned int SIZE_Z = 16;
static constexpr unsigned int SIZE_WHOLE = SIZE_X * SIZE_Y * SIZE_Z;

class Chunk
{
public:
	Chunk();
	Chunk(const std::array<BlockID, SIZE_WHOLE> &chunkData, glm::vec2 position);

    bool IsDisplayed() { return isDisplayed; }

	static constexpr int Index(int x, int y, int z)
    {
    	return x + z * SIZE_X + y * SIZE_X * SIZE_Z;
    }

	uint16_t GetBlock(int x, int y, int z) const
    {
    	return blocks[Index(x, y, z)];
    }

	void SetBlock(int x, int y, int z, uint16_t id)
    {
    	blocks[Index(x, y, z)] = id;
    }

	void Render(GLuint shaderID) const;

	~Chunk();
private:
    bool isDisplayed = false;

    std::array<BlockID, SIZE_WHOLE> blocks{};
	Instanced* *instances;
	uint8_t uniqueCount;
};

