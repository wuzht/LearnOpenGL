#include "MyGLFW.h"

// ��̬����
MyGLFW* MyGLFW::instance = nullptr;

MyGLFW::MyGLFW()
{
}

MyGLFW::~MyGLFW()
{
	// ����Ⱦѭ��������������Ҫ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ
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

MyGLFW * MyGLFW::getInstance()
{
	if (instance == nullptr) {
		instance = new MyGLFW();
	}
	return instance;
}

bool MyGLFW::init(const int scr_width, const int scr_height)
{
	this->scr_width = scr_width;
	this->scr_height = scr_height;
	this->deltaTime = 0.0f;

	glfwInit();	// ��ʼ��GLFW

	// ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// ���汾��(Major)��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// �ΰ汾��(Minor)��Ϊ3

	// ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ���ڵĿ�͸���Ϊ����ǰ��������, ������������ʾ������ڵ����ƣ����⣩
	window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// �ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, MyGLFW::framebuffer_size_callback);
	return true;
}

void MyGLFW::complileAndUseShader(const GLchar * vertexPath, const GLchar * fragmentPath)
{
	// build and compile our shader program
	// -------------------------------------
	ourShader = new Shader(vertexPath, fragmentPath);
	// ������ɫ��
	ourShader->use();
}

void MyGLFW::initImGui(GLFWwindow *t_window)
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

void MyGLFW::startImGui()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void MyGLFW::renderImGui()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MyGLFW::freeImGui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void MyGLFW::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void MyGLFW::processInput(GLFWwindow * window)
{
	// ����û��Ƿ����˷��ؼ�(Esc)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::RIGHT, deltaTime);
}
