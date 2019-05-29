#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

/* 在这里使用的是 glm-0.9.9.5
 * GLM库从0.9.9版本起，默认会将矩阵类型初始化为一个零矩阵（所有元素均为0），
 * 而不是单位矩阵（对角元素为1，其它元素为0）。如果你使用的是0.9.9或0.9.9以上的版本，
 * 你需要将所有的矩阵初始化改为 glm::mat4 mat = glm::mat4(1.0f)。
 * 如果你想与本教程的代码保持一致，请使用低于0.9.9版本的GLM，或者改用上述代码初始化所有的矩阵。*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <iostream>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#include "BezierCurve.h"

/* 将GLFW常用操作封装成MyGLFW类，方便使用 */
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
	// 初始化GLFW
	bool init(const int scr_width, const int scr_height);
	const unsigned int getScrWidth() const { return this->scr_width; };
	const unsigned int getScrHeight() const { return this->scr_height; };

	static void resetCamera();

	/************************* ImGui *************************/
	// 初始化ImGui
	static void initImGui(GLFWwindow *t_window);
	// Start the Dear ImGui frame
	static void startImGui();
	// 渲染循环里调用，渲染ImGui
	static void renderImGui();
	// 释放ImGui资源
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

	// 窗口大小
	unsigned int scr_width;
	unsigned int scr_height;

	static MyGLFW* instance;

	// camera
	static float lastX;
	static float lastY;
	static bool firstMouse;
};