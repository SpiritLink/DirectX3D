#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}

void cPyramid::Setup()
{
	//선을 삽입한다.
	ST_PC_VERTEX p;
	p.c = D3DCOLOR_XRGB(255, 0, 0);
	p.p = D3DXVECTOR3(-5, 0, 0); m_vecLineVertex.push_back(p);
	p.p = D3DXVECTOR3(5, 0, 0); m_vecLineVertex.push_back(p);

	p.c = D3DCOLOR_XRGB(0, 255, 0);
	p.p = D3DXVECTOR3(0, -5, 0); m_vecLineVertex.push_back(p);
	p.p = D3DXVECTOR3(0, 5, 0); m_vecLineVertex.push_back(p);

	p.c = D3DCOLOR_XRGB(0, 0, 255);
	p.p = D3DXVECTOR3(0, 0, -5); m_vecLineVertex.push_back(p);
	p.p = D3DXVECTOR3(0, 0, 5); m_vecLineVertex.push_back(p);

	//삼각형 좌표들을 삽입한다. (가리키는 부분)
	p.c = D3DCOLOR_XRGB(255, 0, 0);
	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, 0.25f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, -0.25f, -0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, -0.25f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, -0.25f, 0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, -0.25f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, 0.25f, 0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, 0.25f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, 0.25f, -0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(1.0f, -0.25f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, 0.25f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, -0.25f, 0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(1.0f, 0.25f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, -0.25f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(1.0f, 0.25f, -0.25f); m_vecTriangleVertex.push_back(p);

	p.c = D3DCOLOR_XRGB(0, 255, 0);
	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(-0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 1.0f, 0.25f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 1.0f, -0.25f); m_vecTriangleVertex.push_back(p);

	p.c = D3DCOLOR_XRGB(0, 0, 255);
	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0, 0, 0); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(-0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);

	p.p = D3DXVECTOR3(0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(-0.25f, 0.25f, 1.0f); m_vecTriangleVertex.push_back(p);
	p.p = D3DXVECTOR3(0.25f, -0.25f, 1.0f); m_vecTriangleVertex.push_back(p);


}

void cPyramid::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecLineVertex.size() / 2,
		&m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size() / 3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));
}
