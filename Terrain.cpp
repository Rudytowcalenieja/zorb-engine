#include "Terrain.h"

float GetHeight(int x, int y)
{
    return stb_perlin_fbm_noise3(
        x * 0.005f,
        y * 0.005f,
        0.0f,
        2.0f,
        0.5f,
        6
    );
}

Terrain::Terrain(unsigned int x, unsigned int y)
{
	sizeX = x;
	sizeY = y;
	height = new int*[sizeX];
    chunks = new Chunk*[sizeX / 16];
    for (unsigned int i = 0; i < x; i++) {
        height[i] = new int[sizeY];
        chunks[i / 16] = new Chunk[sizeY / 16];
        for (unsigned int j = 0; j < y; i++) {
            height[i][j] = GetHeight(i, j);
        }
    }

    for (unsigned int i = 0; i < x; i++) {

        for (unsigned int j = 0; i < x; i++) {
            chunks[i]
        }
    }
}

void Terrain::Render(GLuint shaderID) {
	
}