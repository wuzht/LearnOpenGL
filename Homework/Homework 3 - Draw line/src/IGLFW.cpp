#include "IGLFW.h"

// 静态变量
IGLFW* IGLFW::instance = nullptr;
unsigned int IGLFW::VBO = 0, IGLFW::VAO = 0, IGLFW::EBO = 0;
const unsigned int IGLFW::SCR_WIDTH = 800;
const unsigned int IGLFW::SCR_HEIGHT = 800;

IGLFW::IGLFW()
{
	init();
}

IGLFW::~IGLFW()
{
	// 当渲染循环结束后我们需要正确释放/删除之前的分配的所有资源
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;

	if (ourShader) {
		delete ourShader;
		ourShader = nullptr;
	}
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

IGLFW * IGLFW::getInstance()
{
	if (instance == nullptr) {
		instance = new IGLFW();
	}
	return instance;
}

bool IGLFW::init()
{
	glfwInit();	// 初始化GLFW

	// 告诉GLFW我们要使用的OpenGL版本是3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// 主版本号(Major)设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// 次版本号(Minor)设为3

	// 明确告诉GLFW我们使用的是核心模式(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 窗口的宽和高作为它的前两个参数, 第三个参数表示这个窗口的名称（标题）
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	// 通知GLFW将我们窗口的上下文设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// 在调用任何OpenGL的函数之前我们需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// 注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, IGLFW::framebuffer_size_callback);

	// build and compile our shader program
	// -------------------------------------
	ourShader = new Shader("shader.vs", "shader.fs");
	// 激活着色器
	ourShader->use();

	return true;
}

void IGLFW::initImGui(GLFWwindow *t_window)
{
	const char* glsl_version = "#version 130";
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(t_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void IGLFW::startImGui()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void IGLFW::renderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IGLFW::freeImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void IGLFW::setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 &color)
{
	vertices[verticeIndex * 6 + 3] = color.x;
	vertices[verticeIndex * 6 + 4] = color.y;
	vertices[verticeIndex * 6 + 5] = color.z;
}

void IGLFW::processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[], GLsizeiptr sizeofIndices)
{
	
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
	glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);
	// 4. 设定顶点位置属性指针
	// 使用glVertexAttribPointer函数告诉OpenGL该如何解析顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 5. 设定顶点颜色属性指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindVertexArray(IGLFW::VAO);
}

void IGLFW::freeObjects()
{
	// 释放VAO、VBO、EBO资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

/*
 * 当用户改变窗口的大小的时候，视口也应该被调整。
 * 我们可以对窗口注册一个回调函数(Callback Function)，
 * 它会在每次窗口大小被调整的时候被调用。
 */
void IGLFW::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void IGLFW::processInput(GLFWwindow * window)
{
	// 检查用户是否按下了返回键(Esc)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
