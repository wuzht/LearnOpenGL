#pragma once
#include "MyGLFW.h"

/* Homework 7 - Shadowing Mapping */
class ShadowMapping
{
public:
	ShadowMapping();
	~ShadowMapping();

	void render();

private:
	Shader* shader;
	Shader* simpleDepthShader;
	Shader* debugDepthQuad;
	unsigned int planeVAO;
	unsigned int planeVBO;
	unsigned int cubeVAO;
	unsigned int cubeVBO;
	unsigned int quadVAO;
	unsigned int quadVBO;
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	unsigned int depthMap;
	glm::vec3 lightPos;

	unsigned int woodTexture;

	// utility function for loading a 2D texture from file
	unsigned int loadTexture(char const *path);

	// renders the 3D scene
	void renderScene(const Shader *shader);
	// renderCube() renders a 1x1 3D cube in NDC.
	void renderCube();
	// renderQuad() renders a 1x1 XY quad in NDC
	void renderQuad();
};