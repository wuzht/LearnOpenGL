#pragma once
#include "MyGLFW.h"

class CameraOperation
{
public:
	CameraOperation();
	~CameraOperation();

	float size;	// cube size
	float speed;	// speed of movement
	int option;
	int projection_type;

	// parameters of orthographic projection
	float ortho_left, ortho_right, ortho_bottom, ortho_top, ortho_near, ortho_far;
	// parameters of perspective projection
	float fov; // Field of View

	void render();

private:
	unsigned int texture1, texture2;

	void loadAndCreateTexture();

	/************************* VBO, VAO, EBO *************************/
	unsigned int VBO, VAO, EBO;
	void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	void freeObjects();
};

