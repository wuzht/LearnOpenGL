#include "SimpleGraphics.h"

SimpleGraphics::SimpleGraphics()
{
}

SimpleGraphics::~SimpleGraphics()
{
}

void SimpleGraphics::render(const ImVec4 & edit_color)
{
	MyGLFW::getInstance()->ourShader->setInt("flag", 0);
	// 顶点
	float vertices[] = {
		 0.0f,  1.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 上中 0
		-1.0f, -1.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 左下角 1
		 1.0f, -1.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// 右下角 2

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

	for (int i = 0; i < 9; i++) {
		setVerticesColor(vertices, i, edit_color);
	}
	if (option == 2) {
		setVerticesColor(vertices, 0, ImVec4(1.0f, 0.0f, 0.0f, 1.00f));
		setVerticesColor(vertices, 1, ImVec4(0.0f, 1.0f, 0.0f, 1.00f));
		setVerticesColor(vertices, 2, ImVec4(0.0f, 0.0f, 1.0f, 1.00f));
	}

	processObjects(vertices, sizeof(vertices), indices, sizeof(indices));

	// 按选择绘制各种图形
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

	freeObjects();
}

void SimpleGraphics::setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 & color)
{
	vertices[verticeIndex * 6 + 3] = color.x;
	vertices[verticeIndex * 6 + 4] = color.y;
	vertices[verticeIndex * 6 + 5] = color.z;
}

void SimpleGraphics::processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[], GLsizeiptr sizeofIndices)
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

	glBindVertexArray(VAO);
}

void SimpleGraphics::freeObjects()
{
	// 释放VAO、VBO、EBO资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
