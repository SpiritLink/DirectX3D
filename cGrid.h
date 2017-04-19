#pragma once
class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	std::vector<ST_PC_VERTEX>		m_vecVertex;
	//	std::vector

public:
	void Setup();//인자 알아서
	void Render();
};

