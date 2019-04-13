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
	// ����
	float vertices[] = {
		 0.0f,  1.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// ���� 0
		-1.0f, -1.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// ���½� 1
		 1.0f, -1.0f, 0.0f,	edit_color.x, edit_color.y, edit_color.z,	// ���½� 2

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

	for (int i = 0; i < 9; i++) {
		setVerticesColor(vertices, i, edit_color);
	}
	if (option == 2) {
		setVerticesColor(vertices, 0, ImVec4(1.0f, 0.0f, 0.0f, 1.00f));
		setVerticesColor(vertices, 1, ImVec4(0.0f, 1.0f, 0.0f, 1.00f));
		setVerticesColor(vertices, 2, ImVec4(0.0f, 0.0f, 1.0f, 1.00f));
	}

	processObjects(vertices, sizeof(vertices), indices, sizeof(indices));

	// ��ѡ����Ƹ���ͼ��
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
	glBufferData(GL_ARRAY_BUFFER, sizeofVertices, vertices, GL_STATIC_DRAW);
	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices, indices, GL_STATIC_DRAW);
	// 4. �趨����λ������ָ��
	// ʹ��glVertexAttribPointer��������OpenGL����ν�����������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 5. �趨������ɫ����ָ��
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(VAO);
}

void SimpleGraphics::freeObjects()
{
	// �ͷ�VAO��VBO��EBO��Դ
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
