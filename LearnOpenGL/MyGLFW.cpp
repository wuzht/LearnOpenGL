#include "MyGLFW.h"

// ��̬����
MyGLFW* MyGLFW::instance = nullptr;

float MyGLFW::deltaTime = 0.0f;
float MyGLFW::lastFrame = 0.0f;

Camera MyGLFW::camera;
float MyGLFW::lastX = 0.0f;
float MyGLFW::lastY = 0.0f;
bool MyGLFW::firstMouse = true;

int MyGLFW::hw7_shadow_projection_type = 0;

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
	MyGLFW::lastX = scr_width / 2.0f;
	MyGLFW::lastY = scr_height / 2.0f;

	glfwInit();	// ��ʼ��GLFW

	// ����GLFW����Ҫʹ�õ�OpenGL�汾��3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// ���汾��(Major)��Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// �ΰ汾��(Minor)��Ϊ3

	// ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ���ڵĿ�͸���Ϊ����ǰ��������, ������������ʾ������ڵ����ƣ����⣩
	this->window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", NULL, NULL);
	if (this->window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	// ֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1); // Enable vsync

	// �ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// ע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
	glfwSetCursorPosCallback(this->window, mouse_callback);
	glfwSetScrollCallback(this->window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	this->ourShader = new Shader("GLSL/shader.vs", "GLSL/shader.fs");
	return true;
}

void MyGLFW::resetCamera()
{
	MyGLFW::lastX = 0.0f;
	MyGLFW::lastY = 0.0f;
	MyGLFW::firstMouse = true;
	camera.reset();
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

void MyGLFW::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) MyGLFW::camera.processKeyBoard(Camera::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) MyGLFW::resetCamera();
	if (glfwGetKey(window, GLFW_KEY_O)) MyGLFW::hw7_shadow_projection_type = 0;	// orthographic
	if (glfwGetKey(window, GLFW_KEY_P)) MyGLFW::hw7_shadow_projection_type = 1; // perspective
}

void MyGLFW::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void MyGLFW::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (MyGLFW::firstMouse) {
		MyGLFW::lastX = (float)xpos;
		MyGLFW::lastY = (float)ypos;
		MyGLFW::firstMouse = false;
	}
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top
	MyGLFW::lastX = (float)xpos;
	MyGLFW::lastY = (float)ypos;
	camera.processMouseMovement(xoffset, yoffset);
}

void MyGLFW::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.processMouseScroll((float)yoffset);
}
