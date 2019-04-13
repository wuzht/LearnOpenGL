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
	// 设置顶点颜色
	void setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 &color);
	// 处理各种对象
	void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	// 释放VAO、VBO、EBO资源
	void freeObjects();
};

