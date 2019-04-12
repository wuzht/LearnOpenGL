#if !defined(STB_IMAGE_IMPLEMENTATION)
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "SimpleGraphics.h"
#include "Bresenham.h"
#include "Transformation.h"
#include <string>
#include <iostream>

int main() {
	/******************************** Initializations ************************************/
	MyGLFW::getInstance()->init(800, 800);
	MyGLFW::getInstance()->complileAndUseShader("GLSL/shader.vs", "GLSL/shader.fs");
	MyGLFW::initImGui(MyGLFW::getInstance()->window);

	SimpleGraphics simpleGraphics;
	Bresenham bresenham;
	Transformation transformation;

	/********************************** settings *****************************************/
	ImVec4 edit_color = ImVec4(0.0f, 1.0f, 1.0f, 1.00f);
	std::string homework = "Homework4";
	bool isEnableDepthTest = true;
	glEnable(GL_DEPTH_TEST);	// configure global opengl state
	
	/******************************** Render Loop ****************************************/
	while (!glfwWindowShouldClose(MyGLFW::getInstance()->window)) {
		MyGLFW::processInput(MyGLFW::getInstance()->window);
		glfwPollEvents();

		MyGLFW::startImGui();
		{
			ImGui::Begin("Settings", (bool *)0, ImGuiWindowFlags_MenuBar);
			if (ImGui::BeginMenuBar())
			{
				// 选择作业
				if (ImGui::BeginMenu(homework.c_str()))
				{
					if (ImGui::MenuItem("Homework2", "GUI and Draw simple graphics")) { homework = "Homework2";}
					if (ImGui::MenuItem("Homework3", "Draw line")) { homework = "Homework3";}
					if (ImGui::MenuItem("Homework4", "Transformation")) { homework = "Homework4"; }
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
						if (ImGui::MenuItem("Basic 1/3", "A simple triangle (with color setting)")) { simpleGraphics.option = 1; }
						if (ImGui::MenuItem("Basic 2", "An RGB triangle")) { simpleGraphics.option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Draw other primitives (lines and points)")) { simpleGraphics.option = 3; }
						if (ImGui::MenuItem("Bonus 2", "Draw some triangles with EBO")) { simpleGraphics.option = 4; }
					}
					else if (homework == "Homework3") {
						if (ImGui::MenuItem("Basic 1", "Bresenham Triangle")) { bresenham.option = 1; }
						if (ImGui::MenuItem("Basic 2", "Bresenham Circle")) { bresenham.option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Filled Triangle")) { bresenham.option = 3; }
					}
					else if (homework == "Homework4") {
						if (ImGui::MenuItem("Basic 1", "Simple Cube")) { transformation.option = 1; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Basic 2", "Translation")) { transformation.option = 2; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Basic 3", "Rotation")) { transformation.option = 3; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Basic 4", "Scaling")) { transformation.option = 4; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Bonus 1", "Draw an atom")) { transformation.option = 5; transformation.size = 0.1f; transformation.speed = 10.0f; }
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			if (homework == "Homework2" || homework == "Homework3") {
				ImGui::Text("Color setting");               // Display some text (you can use a format strings too)
				ImGui::ColorEdit3("", (float*)&edit_color); // Edit 3 floats representing a color
			}

			if (homework == "Homework3") {
				const int scr_height = MyGLFW::getInstance()->getScrHeight();
				if (bresenham.option == 1 || bresenham.option == 3) {
					ImGui::Text("Set the vertices of the triangle:");
					ImGui::SliderInt2("vertex1", bresenham.tri_vertices[0], -scr_height, scr_height);
					ImGui::SliderInt2("vertex2", bresenham.tri_vertices[1], -scr_height, scr_height);
					ImGui::SliderInt2("vertex3", bresenham.tri_vertices[2], -scr_height, scr_height);
				}
				else if (bresenham.option == 2) {
					ImGui::Text("Set the radius of the circle:");
					ImGui::SliderInt("radius", &bresenham.radius, 0, scr_height);
				}
				
			}
			else if (homework == "Homework4") {
				ImGui::Checkbox("Enable depth test", &isEnableDepthTest);
				ImGui::SliderFloat("Cube half size", &transformation.size, 0.0f, 3.0f);
				ImGui::SliderFloat("Speed", &transformation.speed, 1.0f, 15.0f);
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		/********************************************************************/

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
		if (isEnableDepthTest && !glIsEnabled(GL_DEPTH_TEST)) glEnable(GL_DEPTH_TEST); 
		else if (!isEnableDepthTest && glIsEnabled(GL_DEPTH_TEST)) glDisable(GL_DEPTH_TEST);

		/*************************** render **********************************/
		if (homework == "Homework2") {
			simpleGraphics.render(edit_color);
		}
		else if (homework == "Homework3") {
			bresenham.render(edit_color);
		}
		else if (homework == "Homework4") {
			transformation.render();
		}
		/********************************************************************/

		MyGLFW::renderImGui();
		glfwSwapBuffers(MyGLFW::getInstance()->window);
	}

	MyGLFW::freeImGui();
	return 0;
}
