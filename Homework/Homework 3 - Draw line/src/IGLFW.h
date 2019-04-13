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
 * ��GLFW���ò�����װ��IGLFW�࣬����ʹ��
 */
class IGLFW
{
public:
	// ���ڴ�С
	static const unsigned int SCR_WIDTH;
	static const unsigned int SCR_HEIGHT;

	GLFWwindow* window;

	// Singleton
	static IGLFW* getInstance();
	
	/************************* ImGui *************************/
	// ��ʼ��ImGui
	static void initImGui(GLFWwindow *t_window);
	// Start the Dear ImGui frame
	static void startImGui();
	// ��Ⱦѭ������ã���ȾImGui
	static void renderImGui();
	// �ͷ�ImGui��Դ
	static void freeImGui();


	/************************* VBO, VAO, EBO *************************/
	// ���ö�����ɫ
	static void setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 &colors);
	// ������ֶ���
	static void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	// �ͷ�VAO��VBO��EBO��Դ
	static void freeObjects();


	/**************************************************************/
	// ÿ�δ��ڴ�С��������ʱ�򱻵��õĻص�����
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	// ���������¼�
	static void processInput(GLFWwindow *window);

private:
	IGLFW();
	~IGLFW();
	// Singleton: disallow the copy constructor and assign operator
	IGLFW(const IGLFW &other) = delete;
	IGLFW & operator=(const IGLFW &other) = delete;

	// ��ʼ��GLFW
	bool init();
	
	static unsigned int VBO, VAO, EBO;
	static IGLFW* instance;
	Shader *ourShader;
};

