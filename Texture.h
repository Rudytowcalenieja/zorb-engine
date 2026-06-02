#pragma once

#include "stb_image.h"

#include <iostream>

#include <GL/glew.h>

class Texture
{
public:
	Texture(const char* location);

	void Use();
	void Unbind();

	GLuint GetID() { return texture; }

	~Texture();
private:
	int width, height, nrChannels;

	GLuint texture;
	unsigned char* data;
};

