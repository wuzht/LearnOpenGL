#include "Utility.h"

Utility::Utility()
{
}


Utility::~Utility()
{
}

void Utility::renderHomework2(const int option, const ImVec4 &edit_color)
{
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
		IGLFW::setVerticesColor(vertices, i, edit_color);
	}
	if (option == 2) {
		IGLFW::setVerticesColor(vertices, 0, ImVec4(1.0f, 0.0f, 0.0f, 1.00f));
		IGLFW::setVerticesColor(vertices, 1, ImVec4(0.0f, 1.0f, 0.0f, 1.00f));
		IGLFW::setVerticesColor(vertices, 2, ImVec4(0.0f, 0.0f, 1.0f, 1.00f));
	}

	IGLFW::processObjects(vertices, sizeof(vertices), indices, sizeof(indices));

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

	IGLFW::freeObjects();
}

std::vector<int> Utility::getBresenhamLinePoints(int x0, int y0, int x1, int y1) const
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

std::vector<int> Utility::getBresenhamCirclePoints(const int x0, const int y0, const int r) const
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

void Utility::getCircleEightPoints(const int x0, const int y0, const int x, const int y, std::vector<int> &points) const
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

std::vector<int> Utility::getRasterizedTrianglePoints(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const
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

std::vector<int> Utility::getEdgeEquation(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const
{
	std::vector<int> params;
	int A = y0 - y1, B = x1 - x0, C = x0 * y1 - x1 * y0;
	if (A * x2 + B * y2 + C < 0) {
		A *= -1; B *= -1; C *= -1;
	}
	params.push_back(A); params.push_back(B); params.push_back(C);
	return params;
}

void Utility::drawFilledTriangle(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2, const ImVec4 & color)
{
	drawPoints(getRasterizedTrianglePoints(x0, y0, x1, y1, x2, y2), color);
}

void Utility::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const ImVec4 &color)
{
	std::vector<int> tri_points[3] = { getBresenhamLinePoints(x0, y0, x1, y1), getBresenhamLinePoints(x0, y0, x2, y2), getBresenhamLinePoints(x2, y2, x1, y1) };
	std::vector<int> points;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < tri_points[i].size(); j++) {
			points.push_back(tri_points[i][j]);
		}
	}
	drawPoints(points, color);
}

void Utility::drawCircle(const int x0, const int y0, const int r, const ImVec4 & color)
{
	drawPoints(getBresenhamCirclePoints(x0, y0, r), color);
}

void Utility::drawPoints(const std::vector<int> points, const ImVec4 &color) const
{
	int pointNum = points.size() / 2;
	float *vertices = makeVertices(points, color);

	IGLFW::processObjects(vertices, pointNum * 6 * sizeof(vertices));

	glDrawArrays(GL_POINTS, 0, pointNum);

	delete[]vertices;
	IGLFW::freeObjects();
}

float * Utility::makeVertices(const std::vector<int> &points, const ImVec4 &color) const
{
	int pointNum = points.size() / 2;
	float *vertices = new float[pointNum * 6];
	for (int i = 0; i < pointNum; i++) {
		// 设置坐标
		vertices[i * 6 + 0] = (float)points[i * 2 + 0] / (float)IGLFW::SCR_WIDTH;
		vertices[i * 6 + 1] = (float)points[i * 2 + 1] / (float)IGLFW::SCR_HEIGHT;
		vertices[i * 6 + 2] = 0.0f;

		// 设置颜色
		vertices[i * 6 + 3] = color.x;
		vertices[i * 6 + 4] = color.y;
		vertices[i * 6 + 5] = color.z;
	}
	return vertices;
}

void Utility::setPixel(std::vector<int>& points, const int x, const int y) const
{
	points.push_back(x); points.push_back(y);
}
