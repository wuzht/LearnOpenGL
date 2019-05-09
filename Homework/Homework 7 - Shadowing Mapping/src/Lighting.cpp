#include "Lighting.h"



Lighting::Lighting()
{
	this->lightingShader = new Shader("GLSL/lighting.vs", "GLSL/lighting.fs");
	this->lampShader = new Shader("GLSL/lamp.vs", "GLSL/lamp.fs");
	/*this->lightPos = glm::vec3(-1.0f, 1.0f, -1.0f);
	this->viewPos = glm::vec3(2.0f, 1.5f, 3.0f);*/

	this->lightPos = glm::vec3(1.0f, 0.8f, 2.0f);
	this->viewPos = glm::vec3(-3.0f, -2.0f, 8.0f);

	this->ambientStrength = 0.1f;
	this->diffuseStrength = 1.0f;
	this->specularStrength = 0.8f;
	this->shininess = 64;
	this->isPhong = 1;
	this->option = 0;
}


Lighting::~Lighting()
{
	if (lightingShader) {
		delete lightingShader;
		lightingShader = nullptr;
	}
	if (lampShader) {
		delete lampShader;
		lampShader = nullptr;
	}
}

void Lighting::render()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	
	// first, configure the cube's VAO (and VBO)
	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	if (option == 1) {
		float speed = 2.0f;
		// change the light's position values over time (can be done anywhere in the render loop actually, but try to do it at least before using the light source positions)
		this->lightPos = glm::vec3(sin(speed * glfwGetTime()) * 2.0f, sin(speed * glfwGetTime() / 2.0f), 2.0f);
	}
	else {
		this->lightPos = glm::vec3(1.0f, 0.8f, 2.0f);
	}
	
	// be sure to activate shader when setting uniforms/drawing objects
	lightingShader->use();
	lightingShader->setInt("isPhong", this->isPhong);
	lightingShader->setFloat("ambientStrength", this->ambientStrength);
	lightingShader->setFloat("diffuseStrength", this->diffuseStrength);
	lightingShader->setFloat("specularStrength", this->specularStrength);
	lightingShader->setInt("shininess", this->shininess);
	lightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	lightingShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	lightingShader->setVec3("lightPos", this->lightPos);
	lightingShader->setVec3("viewPos", this->viewPos);

	// view/projection transformations
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)MyGLFW::getInstance()->getScrWidth() / (float)MyGLFW::getInstance()->getScrHeight(), 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	lightingShader->setMat4("projection", projection);
	lightingShader->setMat4("view", view);

	// world transformation
	glm::mat4 model = glm::mat4(1.0f);
	lightingShader->setMat4("model", model);

	// render the cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	// also draw the lamp object
	lampShader->use();
	lampShader->setMat4("projection", projection);
	lampShader->setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, this->lightPos);
	model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
	lampShader->setMat4("model", model);

	glBindVertexArray(lightVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);


	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
}
