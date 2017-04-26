#include "stdafx.h"
#include "cGrid.h"

#define DISTANCE 15.0f
cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{
	ST_PC_VERTEX v;

	v.c - D3DCOLOR_XRGB(0, 0, 0);
	v.p = D3DXVECTOR3(DISTANCE, 0, 0);															m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);		m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);		m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-DISTANCE, 0, 0);															m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-DISTANCE, 0, 0);															m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(DISTANCE, 0, 0);															m_vecVertex.push_back(v);
}

void cGrid::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecVertex.size() / 2,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}
