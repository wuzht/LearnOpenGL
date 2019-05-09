#pragma once
#include "MyGLFW.h"

/* Homework 6 - Lights and Shading */
class Lighting
{
public:
	Lighting();
	~Lighting();

	int option;
	int isPhong;
	float ambientStrength;
	float diffuseStrength;
	float specularStrength;
	int shininess;

	void render();

private:
	// build and compile our shader program
	Shader *lightingShader;
	Shader *lampShader;

	// lighting
	glm::vec3 lightPos;
	glm::vec3 viewPos;
};

