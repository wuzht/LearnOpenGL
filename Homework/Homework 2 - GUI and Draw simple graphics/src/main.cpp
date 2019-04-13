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
	glfwInit();	// ��ʼ��GLFW

	// ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// ���汾��(Major)��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// �ΰ汾��(Minor)��Ϊ3

	// ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ���ڵĿ�͸���Ϊ����ǰ��������, ������������ʾ������ڵ����ƣ����⣩
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// �ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// build and compile our shader program
	// -------------------------------------
	Shader ourShader("shader.vs", "shader.fs");
	/*************************************************************************/

	// ��ʼ��ImGui
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

	// ��Ⱦѭ��(Render Loop)��������������GLFW�˳�ǰһֱ��������
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
			// ѡ��˵��������ѡ��
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

		// ����
		float vertices[] = {
			 0.0f,  1.0f, 0.0f,	top_color.x, top_color.y, top_color.z,	// ���� 0
			-1.0f, -1.0f, 0.0f,	bottom_left_color.x, bottom_left_color.y, bottom_left_color.z,	// ���½� 1
			 1.0f, -1.0f, 0.0f,	bottom_right_color.x, bottom_right_color.y, bottom_right_color.z,	// ���½� 2

			-0.5f,  0.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// ��0.5 3
			 0.5f,  0.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// ��0.5 4
			 0.0f, -1.0f, 0.0f, edit_color.x, edit_color.y, edit_color.z,	// ���� 5

			// ��
			 0.0f,  0.1f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 6
			 0.0f,  0.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// �� 7
			 0.0f, -0.1f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 8
		};
		// ��������
		unsigned int indices[] = {  // ������0��ʼ
			0, 3, 4,
			1, 3, 5,
			2, 4, 5
		};

		unsigned int VBO, VAO, EBO;
		// 0. ����VAO VBO EBO����
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// 1. �󶨶����������
		glBindVertexArray(VAO);
		// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
		// ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// ����glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ���
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// 4. �趨����λ������ָ��
		// ʹ��glVertexAttribPointer��������OpenGL����ν�����������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// 5. �趨������ɫ����ָ��
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		// 6. ������ɫ��
		ourShader.use();
		/***************************************************************************/
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// ��ѡ����Ƹ���ͼ��
		glBindVertexArray(VAO);
		if (option == 3) {
			glDrawArrays(GL_LINE_LOOP, 0, 2);	// ����
			glDrawArrays(GL_LINE_LOOP, 4, 2);	// ����
			glDrawArrays(GL_POINTS, 6, 3);	// ����
		}
		else if (option == 4) {
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);	// �����������
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, 3);	// ������������
		}

		// ��ȾImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);	// ˫����
		
		// �ͷ�VAO��VBO��EBO��Դ
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	// �ͷ�ImGui��Դ
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	// ����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


/*
 * ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�������
 * ���ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��
 * ������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
	// ����û��Ƿ����˷��ؼ�(Esc)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}