#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

/* ������ʹ�õ��� glm-0.9.9.5
 * GLM���0.9.9�汾��Ĭ�ϻὫ�������ͳ�ʼ��Ϊһ�����������Ԫ�ؾ�Ϊ0����
 * �����ǵ�λ���󣨶Խ�Ԫ��Ϊ1������Ԫ��Ϊ0���������ʹ�õ���0.9.9��0.9.9���ϵİ汾��
 * ����Ҫ�����еľ����ʼ����Ϊ glm::mat4 mat = glm::mat4(1.0f)��
 * ��������뱾�̵̳Ĵ��뱣��һ�£���ʹ�õ���0.9.9�汾��GLM�����߸������������ʼ�����еľ���*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "BezierCurve.h"

/* ��GLFW���ò�����װ��MyGLFW�࣬����ʹ�� */
class MyGLFW
{
public:
	GLFWwindow* window;
	Shader *ourShader;
	static Camera camera;
	
	// timing
	static float deltaTime; // time between current frame and last frame
	static float lastFrame;

	int hw = 8;

	// hw7
	static int hw7_shadow_projection_type;

	/**************************************************************/
	// Singleton
	static MyGLFW* getInstance();
	// ��ʼ��GLFW
	bool init(const int scr_width, const int scr_height);
	const unsigned int getScrWidth() const { return this->scr_width; };
	const unsigned int getScrHeight() const { return this->scr_height; };

	static void resetCamera();

	/************************* ImGui *************************/
	// ��ʼ��ImGui
	static void initImGui(GLFWwindow *t_window);
	// Start the Dear ImGui frame
	static void startImGui();
	// ��Ⱦѭ������ã���ȾImGui
	static void renderImGui();
	// �ͷ�ImGui��Դ
	static void freeImGui();

	/**************************************************************/
	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	static void processInput(GLFWwindow *window);
	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	// glfw: whenever the mouse moves, this callback is called
	static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
	// mouse button
	static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	// key
	static void key_callback(GLFWwindow *window, int key, int scanmode, int action, int mods);

private:
	MyGLFW();
	~MyGLFW();
	// Singleton: disallow the copy constructor and assign operator
	MyGLFW(const MyGLFW &other) = delete;
	MyGLFW & operator=(const MyGLFW &other) = delete;

	// ���ڴ�С
	unsigned int scr_width;
	unsigned int scr_height;

	static MyGLFW* instance;

	// camera
	static float lastX;
	static float lastY;
	static bool firstMouse;
};