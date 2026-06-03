#pragma once

#include "Engine.h"

class Application
{
public:
	Application();

	void CreateMesh();

private:
	std::vector<Mesh> meshList;
};

