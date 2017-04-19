#pragma once
class cPyramid
{
public:
	cPyramid();
	~cPyramid();
private:
	std::vector<ST_PC_VERTEX> m_vecLineVertex;
	std::vector<ST_PC_VERTEX> m_vecTriangleVertex;
public:
	void Setup();
	void Render();
};

