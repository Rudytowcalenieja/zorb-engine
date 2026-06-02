#pragma once

#include "stb_image.h"

#include <iostream>

#include <GL/glew.h>

static unsigned int ids = 0;

class Texture
{
public:
	Texture(const char* location);

	void Use();
	void Unbind();

	GLuint GetID() { return id; }

	~Texture();
private:
	int width, height, nrChannels;

	unsigned int id = ids++;

	GLuint texture;
	unsigned char* data;
};

