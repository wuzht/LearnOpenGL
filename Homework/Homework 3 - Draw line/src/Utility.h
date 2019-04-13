#pragma once
#include "IGLFW.h"
#include <math.h>
#include <algorithm>

class Utility
{
public:
	Utility();
	~Utility();

	/********************* Homework 2 - GUI and Draw simple graphics *********************/
	void renderHomework2(const int option, const ImVec4 &edit_color);

	/***************************** Homework 3 - Draw line *******************************/
	// ��������
	void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, const ImVec4 &color);
	// ��Բ
	void drawCircle(const int x0, const int y0, const int r, const ImVec4 &color);
	// ʹ�������ι�դ���㷨���úͱ�����ͬ����ɫ����������Ρ�
	void drawFilledTriangle(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2, const ImVec4 &color);

private:

	/***************************** Homework 3 - Draw line *******************************/
	// ��points�еĵ㻭����
	void drawPoints(const std::vector<int> points, const ImVec4 &color) const;
	// Bresenham�㷨, ��ȡֱ�ߵĵ�
	std::vector<int> getBresenhamLinePoints(int x0, int y0, int x1, int y1) const;
	// Bresenham�㷨, ��ȡԲ�ĵ�
	std::vector<int> getBresenhamCirclePoints(const int x0, const int y0, const int r) const;
	// ��ȡԲ�˷���ԳƵĵ�
	void getCircleEightPoints(const int x0, const int y0, const int x, const int y, std::vector<int> &points) const;
	// Edge Equation�������������
	std::vector<int> getRasterizedTrianglePoints(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const;
	// ����ֱ�߷���Ax+By+C=0�Ĳ���, ���ز���A, B, C
	std::vector<int> getEdgeEquation(const int x0, const int y0, const int x1, const int y1, const int x2, const int y2) const;

	// ����vertices����
	float *makeVertices(const std::vector<int> &points, const ImVec4 &color) const;
	// ��x, y����points
	void setPixel(std::vector<int> &points, const int x, const int y) const;
};

