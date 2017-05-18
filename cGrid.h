#pragma once
class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	std::vector<ST_PNT_VERTEX> m_vecVertex;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;
	int						m_nTriNum;
	LPDIRECT3DTEXTURE9		m_pTexture;
	D3DMATERIAL9			m_pMaterial;
public:
	void Setup();//���ڴ� �ڱⰡ ����
	void Render();
	void BuildVertexBuffer();
	void BuildMaterial();
	std::vector<ST_PNT_VERTEX> getVertex() { return m_vecVertex; }
};

