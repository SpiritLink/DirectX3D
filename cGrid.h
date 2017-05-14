#pragma once
class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	std::vector<ST_PC_VERTEX> m_vecVertex;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;
	int						m_nLineNum;
public:
	void Setup();//인자는 자기가 설정
	void Render();
	void BuildVertexBuffer();
	std::vector<ST_PC_VERTEX>* getVertex() { return &m_vecVertex; }
};

