#include "Terrain.h"

Terrain::Terrain(unsigned int x, unsigned int y)
{
	sizeX = x;
	sizeY = y;
	height = new int*[sizeX];
	for (int i = 0; i < x; i++) {
		height[i] = new int[sizeY];
	}
}

void Terrain::Render(GLuint shaderID) {
	
}