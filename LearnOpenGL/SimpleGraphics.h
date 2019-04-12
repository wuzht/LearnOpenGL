#pragma once
#include "MyGLFW.h"

/* Homework 2 - GUI and Draw simple graphics */
class SimpleGraphics
{
public:
	SimpleGraphics();
	~SimpleGraphics();

	int option = 1;
	void render(const ImVec4 &edit_color);

private:
	/************************* VBO, VAO, EBO *************************/
	unsigned int VBO, VAO, EBO;
	// ���ö�����ɫ
	void setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 &color);
	// ������ֶ���
	void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	// �ͷ�VAO��VBO��EBO��Դ
	void freeObjects();
};

