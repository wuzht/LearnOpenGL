#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Shader.h"
#include <iostream>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
	glfwInit();	// 初始化GLFW

	// 告诉GLFW我们要使用的OpenGL版本是3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// 主版本号(Major)设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// 次版本号(Minor)设为3

	// 明确告诉GLFW我们使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 窗口的宽和高作为它的前两个参数, 第三个参数表示这个窗口的名称（标题）
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// 在调用任何OpenGL的函数之前我们需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// build and compile our shader program
	// -------------------------------------
	Shader ourShader("shader.vs", "shader.fs");
	/*************************************************************************/

	// 初始化ImGui
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImVec4 top_color = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImVec4 bottom_left_color = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	ImVec4 bottom_right_color = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
	ImVec4 edit_color = ImVec4(0.0f, 1.0f, 1.0f, 1.00f);
	bool my_tool_active = false;
	int option = 1;

	// 渲染循环(Render Loop)，它能在我们让GLFW退出前一直保持运行
	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glfwPollEvents();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
		
	// Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		ImGui::Begin("Settings", &my_tool_active, ImGuiWindowFlags_MenuBar);                          // Create a window called "Hello, world!" and append into it.
		if (ImGui::BeginMenuBar())
		{
			// 选择菜单，按题号选择
			if (ImGui::BeginMenu("Options"))
			{
				if (ImGui::MenuItem("Basic 1/3", "A simple triangle (with color setting)")) { option = 1; }
				if (ImGui::MenuItem("Basic 2", "An RGB triangle")) { option = 2; }
				if (ImGui::MenuItem("Bonus 1", "Draw other primitives (lines and points)")) { option = 3; }
				if (ImGui::MenuItem("Bonus 2", "Draw some triangles with EBO")) { option = 4; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Text("Color setting");               // Display some text (you can use a format strings too)
		ImGui::ColorEdit3("", (float*)&edit_color); // Edit 3 floats representing a color
		ImGui::End();
	}

		if (option != 2) {
			top_color = edit_color;
			bottom_left_color = edit_color;
			bottom_right_color = edit_color;
		}
		else {
			top_color = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
			bottom_left_color = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
			bottom_right_color = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
		}

		// 顶点
		float vertices[] = {
			 0.0f,  1.0f, 0.0f,	top_color.x, top_color.y, top_color.z,	// 上中 0
			-1.0f, -1.0f, 0.0f,	bottom_left_color.x, bottom_left_color.y, bottom_left_color.z,	// 左下角 1
			 1.0f, -1.0f, 0.0f,	bottom_right_color.x, bottom_right_color.y, bottom_right_color.z,	// 右下角 2

			-0.5f,  0.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 左0.5 3
			 0.5f,  0.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 右0.5 4
			 0.0f, -1.0f, 0.0f, edit_color.x, edit_color.y, edit_color.z,	// 下中 5

			// 点
			 0.0f,  0.1f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 6
			 0.0f,  0.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 中 7
			 0.0f, -0.1f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 8
		};
		// 顶点索引
		unsigned int indices[] = {  // 索引从0开始
			0, 3, 4,
			1, 3, 5,
			2, 4, 5
		};

		unsigned int VBO, VAO, EBO;
		// 0. 生成VAO VBO EBO对象
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// 1. 绑定顶点数组对象
		glBindVertexArray(VAO);
		// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
		// 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// 调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// 4. 设定顶点位置属性指针
		// 使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 5. 设定顶点颜色属性指针
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// 6. 激活着色器
		ourShader.use();
		/***************************************************************************/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 按选择绘制各种图形
		glBindVertexArray(VAO);
		if (option == 3) {
			glDrawArrays(GL_LINE_LOOP, 0, 2);	// 画线
			glDrawArrays(GL_LINE_LOOP, 4, 2);	// 画线
			glDrawArrays(GL_POINTS, 6, 3);	// 画点
		}
		else if (option == 4) {
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);	// 画多个三角形
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, 3);	// 画单个三角形
		}

		// 渲染ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);	// 双缓冲
		
		// 释放VAO、VBO、EBO资源
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	// 释放ImGui资源
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	// 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


/*
 * 当用户改变窗口的大小的时候，视口也应该被调整。
 * 我们可以对窗口注册一个回调函数(Callback Function)，
 * 它会在每次窗口大小被调整的时候被调用。
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	// 检查用户是否按下了返回键(Esc)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}