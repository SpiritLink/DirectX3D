#include "stdafx.h"
#include "cGrid.h"

#define DISTANCE 2.0f
#define TILENUM 5
cGrid::cGrid()
	:m_pVertexBuffer(NULL),
	m_nTriNum(0),
	m_pTexture(NULL)
{
}


cGrid::~cGrid()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pTexture);
}

void cGrid::Setup()
{
	m_pTexture = g_pTextureManager->GetTexture("obj/box.jpg");
	ST_PNT_VERTEX v;

	v.n = D3DXVECTOR3(0, 1, 0);
	int nNumHalfTile = TILENUM;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	for (int y = -TILENUM; y < TILENUM; ++y)
	{
		for (int x = -TILENUM; x < TILENUM; ++x)
		{
			v.t = D3DXVECTOR2(0.0f, 0.0f);
			v.p = D3DXVECTOR3(x * DISTANCE			 , 0, y * DISTANCE			 ); m_vecVertex.push_back(v);

			v.t = D3DXVECTOR2(1.0f, 1.0f);
			v.p = D3DXVECTOR3(x * DISTANCE + DISTANCE, 0, y * DISTANCE + DISTANCE); m_vecVertex.push_back(v);

			v.t = D3DXVECTOR2(1.0f, 0.0f);
			v.p = D3DXVECTOR3(x * DISTANCE + DISTANCE, 0, y * DISTANCE			 ); m_vecVertex.push_back(v);

			v.t = D3DXVECTOR2(0.0f, 0.0f);
			v.p = D3DXVECTOR3(x * DISTANCE			 , 0, y * DISTANCE			 ); m_vecVertex.push_back(v);

			v.t = D3DXVECTOR2(0.0f, 1.0f);
			v.p = D3DXVECTOR3(x * DISTANCE			 , 0, y * DISTANCE + DISTANCE); m_vecVertex.push_back(v);

			v.t = D3DXVECTOR2(1.0f, 1.0f);
			v.p = D3DXVECTOR3(x * DISTANCE + DISTANCE, 0, y * DISTANCE + DISTANCE); m_vecVertex.push_back(v);
		}
	}
	BuildVertexBuffer();
}

void cGrid::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	g_pD3DDevice->SetStreamSource(0,
		m_pVertexBuffer,
		0,
		sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
		0,
		m_nTriNum);
}

void cGrid::BuildVertexBuffer()
{
	m_nTriNum = m_vecVertex.size() / 3;
	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		NULL);
	ST_PNT_VERTEX* pv = NULL;
	m_pVertexBuffer->Lock(0, 0, (LPVOID*)&pv, 0);
	memcpy_s(pv, m_vecVertex.size() * sizeof(ST_PNT_VERTEX),&m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVertexBuffer->Unlock();
}
