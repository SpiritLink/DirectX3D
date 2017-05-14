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
	void Setup();//���ڴ� �ڱⰡ ����
	void Render();
	void BuildVertexBuffer();
	std::vector<ST_PC_VERTEX>* getVertex() { return &m_vecVertex; }
};

