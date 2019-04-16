#include "CameraOperation.h"



CameraOperation::CameraOperation()
{
	this->EBO = 0, this->VAO = 0, this->VBO = 0;
	this->texture1 = 0, this->texture2 = 0;
	this->size = 2.0f;
	this->speed = 2.0f;
	this->option = 3;
	this->projection_type = 0;
	this->ortho_left = -10.0f, this->ortho_right = 10.0f, this->ortho_bottom = -10.0f, this->ortho_top = 10.0f, this->ortho_near = -10.0f, this->ortho_far = 30.0f;
	this->fov = 45;

	loadAndCreateTexture();
}


CameraOperation::~CameraOperation()
{
}

void CameraOperation::render()
{
	MyGLFW::getInstance()->ourShader->setInt("flag", 2);
	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-size, -size, -size,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
		 size, -size, -size,	1.0f, 0.0f, 0.0f,	 1.0f, 0.0f,
		 size,  size, -size,	1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		 size,  size, -size,	1.0f, 0.0f, 0.0f,	 1.0f, 1.0f,
		-size,  size, -size,	1.0f, 0.0f, 0.0f,	 0.0f, 1.0f,
		-size, -size, -size,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,

		-size, -size,  size,	0.0f, 1.0f, 0.0f,	 0.0f, 0.0f,
		 size, -size,  size,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
		 size,  size,  size,	0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,
		 size,  size,  size,	0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,
		-size,  size,  size,	0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
		-size, -size,  size,	0.0f, 1.0f, 0.0f,	 0.0f, 0.0f,

		-size,  size,  size,	0.0f, 0.0f, 1.0f,	 1.0f, 0.0f,
		-size,  size, -size,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		-size, -size, -size,	0.0f, 0.0f, 1.0f,	 0.0f, 1.0f,
		-size, -size, -size,	0.0f, 0.0f, 1.0f,	 0.0f, 1.0f,
		-size, -size,  size,	0.0f, 0.0f, 1.0f,	 0.0f, 0.0f,
		-size,  size,  size,	0.0f, 0.0f, 1.0f,	 1.0f, 0.0f,

		 size,  size,  size,	1.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
		 size,  size, -size,	1.0f, 1.0f, 0.0f,	 1.0f, 1.0f,
		 size, -size, -size,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
		 size, -size, -size,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
		 size, -size,  size,	1.0f, 1.0f, 0.0f,	 0.0f, 0.0f,
		 size,  size,  size,	1.0f, 1.0f, 0.0f,	 1.0f, 0.0f,

		-size, -size, -size,	1.0f, 0.0f, 1.0f,	 0.0f, 1.0f,
		 size, -size, -size,	1.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
		 size, -size,  size,	1.0f, 0.0f, 1.0f,	 1.0f, 0.0f,
		 size, -size,  size,	1.0f, 0.0f, 1.0f,	 1.0f, 0.0f,
		-size, -size,  size,	1.0f, 0.0f, 1.0f,	 0.0f, 0.0f,
		-size, -size, -size,	1.0f, 0.0f, 1.0f,	 0.0f, 1.0f,

		-size,  size, -size,	0.0f, 1.0f, 1.0f,	 0.0f, 1.0f,
		 size,  size, -size,	0.0f, 1.0f, 1.0f,	 1.0f, 1.0f,
		 size,  size,  size,	0.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		 size,  size,  size,	0.0f, 1.0f, 1.0f,	 1.0f, 0.0f,
		-size,  size,  size,	0.0f, 1.0f, 1.0f,	 0.0f, 0.0f,
		-size,  size, -size,	0.0f, 1.0f, 1.0f,	 0.0f, 1.0f
	};
	processObjects(vertices, sizeof(vertices));

	// create transformations
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	const float time = speed * (float)glfwGetTime();
	const float sint = std::sin(time);
	const float cost = std::cos(time);
	const float camera_radius = 16.0f;
	switch (option) {
	case 1: {
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, -1.5f));
		view = glm::lookAt(glm::vec3(8.0f, 8.0f, 16.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		if (projection_type == 0) projection = glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top, ortho_near, ortho_far);
		else projection = glm::perspective(glm::radians(fov), (float)MyGLFW::getInstance()->getScrWidth() / (float)MyGLFW::getInstance()->getScrHeight(), 0.1f, 100.0f);
	} break;
	case 2: {
		view = glm::lookAt(glm::vec3(sint * camera_radius, 0.0f, cost * camera_radius), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)MyGLFW::getInstance()->getScrWidth() / (float)MyGLFW::getInstance()->getScrHeight(), 0.1f, 100.0f);
	} break;
	case 3: {
		view = MyGLFW::getInstance()->camera.getViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)MyGLFW::getInstance()->getScrWidth() / (float)MyGLFW::getInstance()->getScrHeight(), 0.1f, 100.0f);
	} break;
	default: break;
	}

	// set matrix
	MyGLFW::getInstance()->ourShader->setMat4("model", model);
	MyGLFW::getInstance()->ourShader->setMat4("view", view);
	MyGLFW::getInstance()->ourShader->setMat4("projection", projection);

	// render
	glDrawArrays(GL_TRIANGLES, 0, 36);
	freeObjects();
}

void CameraOperation::loadAndCreateTexture()
{
	// load and create a texture 
	// -------------------------
	// texture 1
	// ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);	// tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	// texture 2
	// ---------
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("assets/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data) {
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	MyGLFW::getInstance()->ourShader->setInt("texture1", 0);
	MyGLFW::getInstance()->ourShader->setInt("texture2", 1);
}

void CameraOperation::processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[], GLsizeiptr sizeofIndices)
{
	//unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO);

	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
}

void CameraOperation::freeObjects()
{
	// ÊÍ·ÅVAO¡¢VBO¡¢EBO×ÊÔ´
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
