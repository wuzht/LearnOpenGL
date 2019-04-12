#pragma once
#include "MyGLFW.h"
#include <math.h>
#include <algorithm>

/* Homework 3 - Draw line */
class Bresenham
{
public:
	Bresenham();
	~Bresenham();

	int radius = 100;	// 通过ImGui来设置整圆的半径
	int tri_vertices[3][2] = { -50, -50, 50, -50, 0, 50 };	// 通过ImGui来设置三角形顶点位置
	int option = 1;

	void render(const ImVec4 &color);
	// 画三角形
	void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const ImVec4 &color);
	// 画圆
	void drawCircle(const int x0, const int y0, const int r, const ImVec4 &color);
	// 使用三角形光栅化算法，用和背景不同的颜色，填充三角形。
	void drawFilledTriangle(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2, const ImVec4 &color);

private:
	// 将points中的点画出来
	void drawPoints(const std::vector<int> points, const ImVec4 &color);
	// Bresenham算法, 获取直线的点
	std::vector<int> getBresenhamLinePoints(int x0, int y0, int x1, int y1) const;
	// Bresenham算法, 获取圆的点
	std::vector<int> getBresenhamCirclePoints(const int x0, const int y0, const int r) const;
	// 获取圆八方向对称的点
	void getCircleEightPoints(const int x0, const int y0, const int x, const int y, std::vector<int> &points) const;
	// Edge Equation方法填充三角形
	std::vector<int> getRasterizedTrianglePoints(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const;
	// 计算直线方程Ax+By+C=0的参数, 返回参数A, B, C
	std::vector<int> getEdgeEquation(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const;

	// 创建vertices数组
	float *makeVertices(const std::vector<int> &points, const ImVec4 &color) const;
	// 将x, y加入points
	void setPixel(std::vector<int> &points, const int x, const int y) const;

	

	/************************* VBO, VAO, EBO *************************/
	unsigned int VBO, VAO, EBO;
	// 设置顶点颜色
	void setVerticesColor(float vertices[], const int verticeIndex, const ImVec4 &color);
	// 处理各种对象
	void processObjects(float vertices[], GLsizeiptr sizeofVertices, unsigned int indices[] = nullptr, GLsizeiptr sizeofIndices = 0);
	// 释放VAO、VBO、EBO资源
	void freeObjects();
};

