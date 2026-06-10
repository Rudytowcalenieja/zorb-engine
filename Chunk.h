#pragma once

#include <GL/glew.h>
#include <cstdint>
#include <array>
#include "Instanced.h"

using BlockID = uint8_t;

static constexpr unsigned int SIZE_X = 16;
static constexpr unsigned int SIZE_Y = 256;
static constexpr unsigned int SIZE_Z = 16;

class Chunk
{
public:
	Chunk();
	Chunk(std::array<BlockID, SIZE_X * SIZE_Y * SIZE_Z> chunkData, glm::vec3* transforms);

    bool IsDisplayed() { return isDisplayed; }

	void Render(GLuint shaderID);

	~Chunk();
private:
    bool isDisplayed = false;

    std::array<BlockID, SIZE_X * SIZE_Y * SIZE_Z> blocks{};

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

    Instanced instanced;
};

