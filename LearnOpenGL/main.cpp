#if !defined(STB_IMAGE_IMPLEMENTATION)
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "SimpleGraphics.h"
#include "Bresenham.h"
#include "Transformation.h"
#include "CameraOperation.h"
#include "Lighting.h"

int main() {
	/******************************** Initializations ************************************/
	MyGLFW::getInstance()->init(800, 800);
	MyGLFW::initImGui(MyGLFW::getInstance()->window);

	SimpleGraphics simpleGraphics;
	Bresenham bresenham;
	Transformation transformation;
	CameraOperation cameraOperation;
	Lighting lighting;

	/********************************** settings *****************************************/
	ImVec4 edit_color = ImVec4(0.0f, 1.0f, 1.0f, 1.00f);
	int hw = 6;
	bool show_demo_window = false;
	bool isEnableDepthTest = true;
	glEnable(GL_DEPTH_TEST);	// configure global opengl state
	
	/******************************** Render Loop ****************************************/
	while (!glfwWindowShouldClose(MyGLFW::getInstance()->window)) {
		float currentFrame = (float)glfwGetTime();
		MyGLFW::deltaTime = currentFrame - MyGLFW::lastFrame;
		MyGLFW::lastFrame = currentFrame;
		MyGLFW::processInput(MyGLFW::getInstance()->window);
		
		MyGLFW::startImGui();
		{
			ImGui::Begin("Settings", (bool *)0, ImGuiWindowFlags_MenuBar);
			if (ImGui::BeginMenuBar())
			{
				// Choose homework
				if (ImGui::BeginMenu( (std::string("Homework") + std::to_string(hw)).c_str() ))
				{
					if (ImGui::BeginMenu("Homework2")) {		
						if (ImGui::MenuItem("Basic 1/3", "A simple triangle (with color setting)")) { hw = 2; simpleGraphics.option = 1; }
						if (ImGui::MenuItem("Basic 2", "An RGB triangle")) { hw = 2; simpleGraphics.option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Draw other primitives (lines and points)")) { hw = 2; simpleGraphics.option = 3; }
						if (ImGui::MenuItem("Bonus 2", "Draw some triangles with EBO")) { hw = 2; simpleGraphics.option = 4; }
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Homework3")) {
						if (ImGui::MenuItem("Basic 1", "Bresenham Triangle")) { hw = 3; bresenham.option = 1; }
						if (ImGui::MenuItem("Basic 2", "Bresenham Circle")) { hw = 3; bresenham.option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Filled Triangle")) { hw = 3; bresenham.option = 3; }
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Homework4")) {
						if (ImGui::MenuItem("Basic 1", "Simple Cube")) { hw = 4; transformation.option = 1; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Basic 2", "Translation")) { hw = 4; transformation.option = 2; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Basic 3", "Rotation")) { hw = 4; transformation.option = 3; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Basic 4", "Scaling")) { hw = 4; transformation.option = 4; transformation.size = 2.0f; transformation.speed = 3.0f; }
						if (ImGui::MenuItem("Bonus 1", "Draw an atom")) { hw = 4; transformation.option = 5; transformation.size = 0.1f; transformation.speed = 10.0f; }
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Homework5")) {
						if (ImGui::MenuItem("Basic 1", "Projection")) { hw = 5; cameraOperation.option = 1; }
						if (ImGui::MenuItem("Basic 2", "View Changing")) { hw = 5; cameraOperation.option = 2; }
						if (ImGui::MenuItem("Bonus 1", "Look around")) { hw = 5; cameraOperation.option = 3; MyGLFW::getInstance()->resetCamera(); }
						ImGui::EndMenu();
					}
					if (ImGui::BeginMenu("Homework6")) {
						if (ImGui::MenuItem("Basic", "Lighting Model")) { hw = 6; }
						if (ImGui::MenuItem("Bonus 1", "Move light")) { hw = 6; }
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenuBar();
			}

			// Demo Window
			if (show_demo_window) ImGui::ShowDemoWindow(); 
			//ImGui::Checkbox("Demo Window", &show_demo_window);

			switch (hw)
			{
				case 2: {
					ImGui::Text("Homework2 - GUI and Draw simple graphics");
					ImGui::Text("Color setting");
					ImGui::ColorEdit3("", (float*)& edit_color);
				} break;
				case 3: {
					ImGui::Text("Homework3 - Draw line");
					ImGui::Text("Color setting");
					ImGui::ColorEdit3("", (float*)& edit_color);
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
				} break;
				case 4: {
					ImGui::Text("Homework4 - Transformation");
					ImGui::Checkbox("Enable depth test", &isEnableDepthTest);
					ImGui::SliderFloat("Cube half size", &transformation.size, 0.0f, 3.0f);
					ImGui::SliderFloat("Speed", &transformation.speed, 1.0f, 15.0f);
				} break;
				case 5: {
					ImGui::Text("Homework5 - Camera");
					ImGui::Checkbox("Enable depth test", &isEnableDepthTest);
					if (cameraOperation.option == 1) {
						ImGui::RadioButton("orthographic", &cameraOperation.projection_type, 0); ImGui::SameLine();
						ImGui::RadioButton("perspective", &cameraOperation.projection_type, 1);
						if (cameraOperation.projection_type == 0) {
							ImGui::SliderFloat("left", &cameraOperation.ortho_left, -20.0f, 0.0f);
							ImGui::SliderFloat("right", &cameraOperation.ortho_right, 0.0f, 20.0f);
							ImGui::SliderFloat("bottom", &cameraOperation.ortho_bottom, -20.f, 0.0f);
							ImGui::SliderFloat("top", &cameraOperation.ortho_top, 0.0f, 20.0f);
							ImGui::SliderFloat("near", &cameraOperation.ortho_near, -30.0f, 30.0f);
							ImGui::SliderFloat("far", &cameraOperation.ortho_far, -30.0f, 30.0f);
						}
						else {
							ImGui::SliderFloat("fov", &cameraOperation.fov, 20.0f, 150.0f);
						}
					}
					
				} break;
				case 6: {
					ImGui::Text("Homework6 - Lights and Shading");
					ImGui::Checkbox("Enable depth test", &isEnableDepthTest);
					ImGui::RadioButton("Phong", &lighting.isPhong, 1); ImGui::SameLine();
					ImGui::RadioButton("Gouraud", &lighting.isPhong, 0);
					ImGui::SliderFloat("ambient", &lighting.ambientStrength, 0.0f, 1.0f);
					ImGui::SliderFloat("diffuse", &lighting.diffuseStrength, 0.0f, 1.0f);
					ImGui::SliderFloat("specular", &lighting.specularStrength, 0.0f, 1.0f);
					ImGui::SliderInt("shininess", &lighting.shininess, 2, 256);
				} break;
				default: break;
			}

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		/********************************************************************/

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
		if (isEnableDepthTest && !glIsEnabled(GL_DEPTH_TEST)) glEnable(GL_DEPTH_TEST); 
		else if (!isEnableDepthTest && glIsEnabled(GL_DEPTH_TEST)) glDisable(GL_DEPTH_TEST);

		/*************************** render **********************************/
		switch (hw)
		{
			case 2: simpleGraphics.render(edit_color); break;
			case 3: bresenham.render(edit_color); break;
			case 4: transformation.render(); break;
			case 5: cameraOperation.render(); break;
			case 6: lighting.render(); break;
			default: break;
		}
		MyGLFW::renderImGui();
		/********************************************************************/

		glfwSwapBuffers(MyGLFW::getInstance()->window);
		glfwPollEvents();
	}

	MyGLFW::freeImGui();
	return 0;
}
