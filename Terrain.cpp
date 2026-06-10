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
	// height = new int*[sizeX];
 //    chunks = new Chunk*[sizeX / 16];
 //    for (unsigned int i = 0; i < x; i++) {
 //        height[i] = new int[sizeY];
 //        chunks[i / 16] = new Chunk[sizeY / 16];
 //        for (unsigned int j = 0; j < y; i++) {
 //            height[i][j] = GetHeight(i, j);
 //            chunks[i / 16][j / 16];
 //        }
 //    }

	for (int i = 0; i < sizeX * sizeY; i++) {
		std::array<BlockID, SIZE_X * SIZE_Y * SIZE_Z> blocks;
		for (int j = 0; j < SIZE_X * SIZE_Z; j++) {

		}
		Chunk* chunk = new Chunk(blocks, glm::vec3(0, 0, 0));
		chunks.insert(std::pair<unsigned int, Chunk*>(i, NULL));
	}
}

void Terrain::Render(GLuint shaderID) {
	
}