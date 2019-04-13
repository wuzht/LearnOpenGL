#include "Utility.h"
#include <string>

Utility utility;

int main() {
	IGLFW *myGLFW = IGLFW::getInstance();

	IGLFW::initImGui(myGLFW->window);

	/****************************** 用于ImGui的变量 ******************************************/
	ImVec4 edit_color = ImVec4(0.0f, 1.0f, 1.0f, 1.00f);
	int option = 1;
	std::string homework = "Homework3";

	/* homework3的变量 */
	int hw3_tri_vertices[3][2] = { -50, -50, 50, -50, 0, 50 };
	int radius = 100;
	/**************************************************************************************/
	
	/*const double maxFPS = 60.0;
	const double maxPeriod = 1.0 / maxFPS;
	double lastTime = 0.0;*/
	// 渲染循环(Render Loop)，它能在我们让GLFW退出前一直保持运行
	while (!glfwWindowShouldClose(myGLFW->window)) {
		/*double time = glfwGetTime();
		double deltaTime = time - lastTime;
		if (deltaTime < maxPeriod) {
			continue;
		}
		lastTime = time;*/

		IGLFW::processInput(myGLFW->window);
		glfwPollEvents();

		IGLFW::startImGui();

		// Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			ImGui::Begin("Settings", (bool *)0, ImGuiWindowFlags_MenuBar);  // Create a window called "Hello, world!" and append into it.
			if (ImGui::BeginMenuBar())
			{
				// 选择作业
				if (ImGui::BeginMenu(homework.c_str()))
				{
					if (ImGui::MenuItem("Homework2", "GUI and Draw simple graphics")) { option = 1; homework = "Homework2";}
					if (ImGui::MenuItem("Homework3", "Draw line")) { option = 1; homework = "Homework3";}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}
			if (ImGui::BeginMenuBar())
			{
				// 选择该作业的题号
				if (ImGui::BeginMenu("Options"))
				{
					if (homework == "Homework2") {
						if (ImGui::MenuItem("Basic 1/3", "A simple triangle (with color setting)")) { option = 1; }
						if (ImGui::MenuItem("Basic 2", "An RGB triangle")) { option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Draw other primitives (lines and points)")) { option = 3; }
						if (ImGui::MenuItem("Bonus 2", "Draw some triangles with EBO")) { option = 4; }
					}
					else if (homework == "Homework3") {
						if (ImGui::MenuItem("Basic 1", "Bresenham Triangle")) { option = 1; }
						if (ImGui::MenuItem("Basic 2", "Bresenham Circle")) { option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Filled Triangle")) { option = 3; }
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			ImGui::Text("Color setting");               // Display some text (you can use a format strings too)
			ImGui::ColorEdit3("", (float*)&edit_color); // Edit 3 floats representing a color

			if (homework == "Homework3") {
				if (option == 1 || option == 3) {
					ImGui::Text("Set the vertices of the triangle:");
					ImGui::SliderInt2("vertex1", hw3_tri_vertices[0], -(int)IGLFW::SCR_HEIGHT, (int)IGLFW::SCR_HEIGHT);
					ImGui::SliderInt2("vertex2", hw3_tri_vertices[1], -(int)IGLFW::SCR_HEIGHT, (int)IGLFW::SCR_HEIGHT);
					ImGui::SliderInt2("vertex3", hw3_tri_vertices[2], -(int)IGLFW::SCR_HEIGHT, (int)IGLFW::SCR_HEIGHT);
				}
				else if (option == 2) {
					ImGui::Text("Set the radius of the circle:");
					ImGui::SliderInt("radius", &radius, 0, (int)IGLFW::SCR_HEIGHT);
				}
				
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (homework == "Homework2") {
			utility.renderHomework2(option, edit_color);
		}
		else if (homework == "Homework3") {
			if (option == 1) {
				utility.drawTriangle(hw3_tri_vertices[0][0], hw3_tri_vertices[0][1], hw3_tri_vertices[1][0],
					hw3_tri_vertices[1][1], hw3_tri_vertices[2][0], hw3_tri_vertices[2][1], edit_color);
			}
			else if (option == 2) {
				utility.drawCircle(0, 0, radius, edit_color);
			}
			else {
				utility.drawFilledTriangle(hw3_tri_vertices[0][0], hw3_tri_vertices[0][1], hw3_tri_vertices[1][0],
					hw3_tri_vertices[1][1], hw3_tri_vertices[2][0], hw3_tri_vertices[2][1], edit_color);
			}
		}

		IGLFW::renderImGui();
		glfwSwapBuffers(myGLFW->window);	// 双缓冲
	}

	IGLFW::freeImGui();
	return 0;
}
