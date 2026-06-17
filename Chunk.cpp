#include "Chunk.h"

Chunk::Chunk() {
	blocks.fill(0);
}

Chunk::Chunk(const std::array<BlockID, SIZE_WHOLE> &chunkData, const glm::vec2 position) {
	GLfloat vertices[] = {

		// FRONT
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,

		 // BACK
		 -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		  0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,

		  // LEFT
		  -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		  -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		  -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		  -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,

		  // RIGHT
		   0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		   0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		   0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		   0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,

		   // TOP
		   -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
			0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		   -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,

			// BOTTOM
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f
	};

	GLuint indices[] = {
		0,  1,  2,   1,  3,  2,   // front
		4,  5,  6,   5,  7,  6,   // back
		8,  9, 10,   9, 11, 10,   // left
	   12, 13, 14,  13, 15, 14,   // right
	   16, 17, 18,  17, 19, 18,   // top
	   20, 21, 22,  21, 23, 22    // bottom
	};

	blocks = chunkData;

	// Counting unique BlockIDs
	// std::array<int, 256> counts{};
	//
	// for (const BlockID id : blocks)
	// {
	// 	counts[id]++;
	// }
	// uniqueCount = 0;
	// for (int c : counts) {
	// 	if (c > 0) uniqueCount++;
	// }
	//
	// int solid = 0;
	//
	// for (auto b : blocks)
	// {
	// 	if (b != 0)
	// 		solid++;
	// }

	// printf("solid blocks = %d\n", solid);

	// Creating instances and setting transforms
	instances = new Instanced*[256]{};
	for (int id = 1; id < 256; id++)
	{
		std::vector<glm::vec3> transforms;
		for (int i = 0; i < blocks.size(); i++)
		{
			if ((blocks[i]) != id)
				continue;

			int x = i % SIZE_X;
			int z = (i / SIZE_X) % SIZE_Z;
			int y = i / (SIZE_X * SIZE_Z);

			transforms.emplace_back(x, y, z);
		}
		if (!transforms.empty())
			printf("ID %d -> %zu transforms\n", id, transforms.size());

		// printf("uniqueCount = %d\n", uniqueCount);
		// printf("transforms = %zu\n", transforms.size());
		instances[id] = new Instanced();
		instances[id]->CreateMesh(vertices, 192, indices, 36);
		instances[id]->CreateInstanced(transforms.data(), transforms.size());
		instances[id]->Transform(glm::vec3(position.x, 0.0f, position.y));
	}
}

void Chunk::Render(const GLuint shaderID) const {
	for (int i = 0; i < 256; i++) {
		if (instances[i]) instances[i]->Render(shaderID);
	}
}

Chunk::~Chunk() {
	for (int i = 0; i < 256; i++)
	{
		delete instances[i];
	}
	delete[] instances;
}