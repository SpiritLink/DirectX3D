#include "stdafx.h"
#include "cGrid.h"

#define DISTANCE 10.0f
#define TILENUM 50
cGrid::cGrid()
{
}


cGrid::~cGrid()
{
}

void cGrid::Setup()
{
	ST_PC_VERTEX v;

	int nNumHalfTile = TILENUM;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		v.c = D3DCOLOR_XRGB(0, 0, 0);
		v.p = D3DXVECTOR3(fMin, 0, i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); m_vecVertex.push_back(v);
	}

	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);
	//v.c - D3DCOLOR_XRGB(0, 0, 0);
	//v.p = D3DXVECTOR3(DISTANCE, 0, 0);															m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);		m_vecVertex.push_back(v);

	//v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);		m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);

	//v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-DISTANCE, 0, 0);															m_vecVertex.push_back(v);

	//v.p = D3DXVECTOR3(-DISTANCE, 0, 0);															m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);

	//v.p = D3DXVECTOR3(-cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);

	//v.p = D3DXVECTOR3(cosf(D3DX_PI / 3.0f) * DISTANCE, 0, -sinf(D3DX_PI / 3.0f) * DISTANCE);	m_vecVertex.push_back(v);
	//v.p = D3DXVECTOR3(DISTANCE, 0, 0);															m_vecVertex.push_back(v);
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
