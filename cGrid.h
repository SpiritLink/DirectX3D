#pragma once
class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	std::vector<ST_PC_VERTEX> m_vecVertex;
	//	std::vector<
public:
	void Setup();//���ڴ� �ڱⰡ ����
	void Render();
	std::vector<ST_PC_VERTEX>* getVertex() { return &m_vecVertex; }
};

