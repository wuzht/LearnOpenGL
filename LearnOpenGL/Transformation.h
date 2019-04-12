#pragma once
#include "MyGLFW.h"
#include <random>

/* Homework 4 - Transformation */
class Transformation
{
public:
	Transformation();
	~Transformation();

	float size = 2.0f;	// cube size
	float speed = 3.0f;	// speed of movement
	int option = 1;

	void render();

private:
	unsigned int texture1, texture2;
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	std::vector<glm::vec3> cubeTransParams;
	std::default_random_engine random;

	void loadAndCreateTexture();

	/************************* VBO, VAO, EBO *************************/
	unsigned int VBO, VAO, EBO;
	void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	void freeObjects();
};

