#include "Bresenham.h"

Bresenham::Bresenham()
{
}

Bresenham::~Bresenham()
{
}

void Bresenham::render(const ImVec4 & color)
{
	MyGLFW::getInstance()->ourShader->use();
	if (option == 1) {
		drawTriangle(tri_vertices[0][0], tri_vertices[0][1], tri_vertices[1][0],
			tri_vertices[1][1], tri_vertices[2][0], tri_vertices[2][1], color);
	}
	else if (option == 2) {
		drawCircle(0, 0, radius, color);
	}
	else {
		drawFilledTriangle(tri_vertices[0][0], tri_vertices[0][1], tri_vertices[1][0],
			tri_vertices[1][1], tri_vertices[2][0], tri_vertices[2][1], color);
	}
}

void Bresenham::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const ImVec4 & color)
{
	std::vector<int> tri_points[3] = { getBresenhamLinePoints(x0, y0, x1, y1), getBresenhamLinePoints(x0, y0, x2, y2), getBresenhamLinePoints(x2, y2, x1, y1) };
	std::vector<int> points;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < (int)tri_points[i].size(); j++) {
			points.push_back(tri_points[i][j]);
		}
	}
	drawPoints(points, color);
}

void Bresenham::drawCircle(const int x0, const int y0, const int r, const ImVec4 & color)
{
	drawPoints(getBresenhamCirclePoints(x0, y0, r), color);
}

void Bresenham::drawFilledTriangle(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2, const ImVec4 & color)
{
	drawPoints(getRasterizedTrianglePoints(x0, y0, x1, y1, x2, y2), color);
}

void Bresenham::drawPoints(const std::vector<int> points, const ImVec4 & color)
{
	MyGLFW::getInstance()->ourShader->setInt("flag", 0);
	int pointNum = points.size() / 2;
	float *vertices = makeVertices(points, color);

	processObjects(vertices, pointNum * 6 * sizeof(vertices));

	glDrawArrays(GL_POINTS, 0, pointNum);

	delete[]vertices;
	freeObjects();
}

std::vector<int> Bresenham::getBresenhamLinePoints(int x0, int y0, int x1, int y1) const
{
	std::vector<int> points;
	int dx = abs(x1 - x0), dy = abs(y1 - y0);
	const bool steep = dy > dx;
	if (steep) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		std::swap(dx, dy);
	}
	const int ix = x1 - x0 > 0 ? 1 : -1;
	const int iy = y1 - y0 > 0 ? 1 : -1;
	int x = x0, y = y0;
	const int delta_p1 = 2 * dy;
	const int delta_p2 = 2 * (dy - dx);
	int p = 2 * dy - dx;

	while (x != x1) {
		if (p < 0) {
			p += delta_p1;
		}
		else {
			y += iy;
			p += delta_p2;
		}
		x += ix;
		steep ? setPixel(points, y, x) : setPixel(points, x, y);
	}
	return points;
}

std::vector<int> Bresenham::getBresenhamCirclePoints(const int x0, const int y0, const int r) const
{
	std::vector<int> points;
	int x = 0, y = r, p = 3 - 2 * r;
	while (x <= y) {
		getCircleEightPoints(x0, y0, x, y, points);
		if (p < 0) {
			p += 4 * x + 6;
		}
		else {
			p += 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	return points;
}

void Bresenham::getCircleEightPoints(const int x0, const int y0, const int x, const int y, std::vector<int>& points) const
{
	setPixel(points, x0 + x, y0 + y);
	setPixel(points, x0 + x, y0 - y);
	setPixel(points, x0 - x, y0 + y);
	setPixel(points, x0 - x, y0 - y);
	setPixel(points, x0 + y, y0 + x);
	setPixel(points, x0 + y, y0 - x);
	setPixel(points, x0 - y, y0 + x);
	setPixel(points, x0 - y, y0 - x);
}

std::vector<int> Bresenham::getRasterizedTrianglePoints(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const
{
	std::vector<int> points;
	int x_min = std::min(x0, std::min(x1, x2));
	int y_min = std::min(y0, std::min(y1, y2));
	int x_max = std::max(x0, std::max(x1, x2));
	int y_max = std::max(y0, std::max(y1, y2));
	std::vector<std::vector<int>> equations = { getEdgeEquation(x0, y0, x1, y1, x2, y2), getEdgeEquation(x0, y0, x2, y2, x1, y1), getEdgeEquation(x2, y2, x1, y1, x0, y0) };
	for (int x = x_min; x <= x_max; x++) {
		for (int y = y_min; y <= y_max; y++) {
			bool inside = true;
			for (int i = 0; i < (int)equations.size(); i++) {
				if (equations[i][0] * x + equations[i][1] * y + equations[i][2] < 0) {
					inside = false;
					break;
				}
			}
			if (inside) {
				setPixel(points, x, y);
			}
		}
	}
	return points;
}

std::vector<int> Bresenham::getEdgeEquation(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const
{
	std::vector<int> params;
	int A = y0 - y1, B = x1 - x0, C = x0 * y1 - x1 * y0;
	if (A * x2 + B * y2 + C < 0) {
		A *= -1; B *= -1; C *= -1;
	}
	params.push_back(A); params.push_back(B); params.push_back(C);
	return params;
}

float * Bresenham::makeVertices(const std::vector<int>& points, const ImVec4 & color) const
{
	int pointNum = points.size() / 2;
	float *vertices = new float[pointNum * 6];
	for (int i = 0; i < pointNum; i++) {
		// 设置坐标
		vertices[i * 6 + 0] = (float)points[i * 2 + 0] / (float)MyGLFW::getInstance()->getScrWidth();
		vertices[i * 6 + 1] = (float)points[i * 2 + 1] / (float)MyGLFW::getInstance()->getScrHeight();
		vertices[i * 6 + 2] = 0.0f;

		// 设置颜色
		vertices[i * 6 + 3] = color.x;
		vertices[i * 6 + 4] = color.y;
		vertices[i * 6 + 5] = color.z;
	}
	return vertices;
}

void Bresenham::setPixel(std::vector<int>& points, const int x, const int y) const
{
	points.push_back(x); points.push_back(y);
}

void Bresenham::setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 & color)
{
	vertices[verticeIndex * 6 + 3] = color.x;
	vertices[verticeIndex * 6 + 4] = color.y;
	vertices[verticeIndex * 6 + 5] = color.z;
}

void Bresenham::processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[], GLsizeiptr sizeofIndices)
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

	/*glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/
	glBindVertexArray(VAO);
}

void Bresenham::freeObjects()
{
	// 释放VAO、VBO、EBO资源
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
