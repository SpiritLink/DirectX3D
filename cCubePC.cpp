#include "stdafx.h"
#include "cCubePc.h"


cCubePc::cCubePc()
	:m_vDirection(0, 0, 1)
	, m_vPosition(0, 0, 0)
	, m_fRotY(0.0f)

{
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePc::~cCubePc()
{
}

void cCubePc::Setup()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(0, 255, 255);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 0.0f); m_vecVertex.push_back(v);

}

void cCubePc::Update()
{

}

void cCubePc::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & cCubePc::GetPosition()
{
	return m_vPosition;
	// TODO: 여기에 반환 구문을 삽입합니다.
}
