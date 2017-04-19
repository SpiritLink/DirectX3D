#include "stdafx.h"
#include "cGrid.h"


cGrid::cGrid()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0, 2, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, -2, 0); m_vecVertex.push_back(v);


}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{
}

void cGrid::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
