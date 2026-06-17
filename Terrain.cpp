#include "Terrain.h"

float GetHeight(int x, int z)
{
    return stb_perlin_fbm_noise3(
        x * 0.1f,
        z * 0.1f,
        0.0f,
        2.0f,
        0.5f,
        6
    );
}

Terrain::Terrain() {

}

void Terrain::GenerateTerrain(unsigned int chunks_length, unsigned int chunks_width) {
	sizeX = chunks_length;
	sizeZ = chunks_width;

	for (int i = 0; i < chunks_length * chunks_width; i++) {
		std::array<BlockID, SIZE_X * SIZE_Y * SIZE_Z> blocks{};
		for (int j = 0; j < SIZE_X * SIZE_Z; j++) {
			uint8_t x = j % SIZE_X;
			uint8_t z = j / SIZE_X;
			uint8_t y = static_cast<uint8_t>((GetHeight(x, z) + 1.0f) * 2.0f);
			blocks[Chunk::Index(x, y, z)] = 1;
		}
		int cx = i % chunks_length;
		int cz = i / chunks_length;
		Chunk* chunk = new Chunk(blocks, glm::vec2(cx * sizeX, cz * sizeZ));
		chunks.insert(std::pair<unsigned int, Chunk*>(i, chunk));
		printf("chunks[%d] created!\n", i);
	}
}

// TODO FIX RENDERING
void Terrain::Render(GLuint shaderID, Frustum frustum) {
	for (int i = 0; i < sizeX * sizeZ; i++) {
		AABB aabb;
		uint8_t x = i % SIZE_X;
		uint8_t z = i / SIZE_X;
		aabb.min = glm::vec3(1.0f + 16.0f * x, 0, 1.0f + 16.0f * z);
		aabb.max = glm::vec3(16.0f + 16.0f * x, 256.0f, 16.0f + 16.0f * (z + 1));
		if (IsVisible(aabb, frustum)) {
			chunks[i]->Render(shaderID);
			// printf("chunks[%d] rendered!\n", i);
		}
	}
}

Terrain::~Terrain() {
	chunks.clear();
}