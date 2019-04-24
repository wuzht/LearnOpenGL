#pragma once
#include "MyGLFW.h"

class Lighting
{
public:
	Lighting();
	~Lighting();

	void render();

private:
	// build and compile our shader program
	Shader *lightingShader;
	Shader *lampShader;

	// lighting
	glm::vec3 lightPos;
};

