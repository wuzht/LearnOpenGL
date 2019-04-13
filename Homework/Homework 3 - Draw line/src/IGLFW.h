#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Shader.h"
#include <iostream>
#include <vector>

/*
 * 将GLFW常用操作封装成IGLFW类，方便使用
 */
class IGLFW
{
public:
	// 窗口大小
	static const unsigned int SCR_WIDTH;
	static const unsigned int SCR_HEIGHT;

	GLFWwindow* window;

	// Singleton
	static IGLFW* getInstance();
	
	/************************* ImGui *************************/
	// 初始化ImGui
	static void initImGui(GLFWwindow *t_window);
	// Start the Dear ImGui frame
	static void startImGui();
	// 渲染循环里调用，渲染ImGui
	static void renderImGui();
	// 释放ImGui资源
	static void freeImGui();


	/************************* VBO, VAO, EBO *************************/
	// 设置顶点颜色
	static void setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 &colors);
	// 处理各种对象
	static void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	// 释放VAO、VBO、EBO资源
	static void freeObjects();


	/**************************************************************/
	// 每次窗口大小被调整的时候被调用的回调函数
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	// 处理输入事件
	static void processInput(GLFWwindow *window);

private:
	IGLFW();
	~IGLFW();
	// Singleton: disallow the copy constructor and assign operator
	IGLFW(const IGLFW &other) = delete;
	IGLFW & operator=(const IGLFW &other) = delete;

	// 初始化GLFW
	bool init();
	
	static unsigned int VBO, VAO, EBO;
	static IGLFW* instance;
	Shader *ourShader;
};

