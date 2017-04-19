#include "stdafx.h"
#include "cCubePC.h"

#define MOVESPEED 0.1f

cCubePC::cCubePC()
	: m_vDirection(0, 0, 1)	//보는 방향
	, m_vPosition(0, 0, 0)	//위치
	, m_fRotY(0.0f)			//회전값
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	//삼각형 하나만 그리게끔 시범을 보여줌
	D3DXVECTOR3 ptVector[8];
	ptVector[0] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	ptVector[1] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	ptVector[2] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	ptVector[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	ptVector[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	ptVector[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	ptVector[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	ptVector[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	ST_PC_VERTEX v;

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = ptVector[0]; m_vecVertex.push_back(v);
	v.p = ptVector[1]; m_vecVertex.push_back(v);
	v.p = ptVector[2]; m_vecVertex.push_back(v);
	v.p = ptVector[0]; m_vecVertex.push_back(v);
	v.p = ptVector[2]; m_vecVertex.push_back(v);
	v.p = ptVector[3]; m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = ptVector[4]; m_vecVertex.push_back(v);
	v.p = ptVector[6]; m_vecVertex.push_back(v);
	v.p = ptVector[5]; m_vecVertex.push_back(v);
	v.p = ptVector[4]; m_vecVertex.push_back(v);
	v.p = ptVector[7]; m_vecVertex.push_back(v);
	v.p = ptVector[6]; m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = ptVector[4]; m_vecVertex.push_back(v);
	v.p = ptVector[5]; m_vecVertex.push_back(v);
	v.p = ptVector[1]; m_vecVertex.push_back(v);
	v.p = ptVector[4]; m_vecVertex.push_back(v);
	v.p = ptVector[1]; m_vecVertex.push_back(v);
	v.p = ptVector[0]; m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = ptVector[3]; m_vecVertex.push_back(v);
	v.p = ptVector[2]; m_vecVertex.push_back(v);
	v.p = ptVector[6]; m_vecVertex.push_back(v);
	v.p = ptVector[3]; m_vecVertex.push_back(v);
	v.p = ptVector[6]; m_vecVertex.push_back(v);
	v.p = ptVector[7]; m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = ptVector[1]; m_vecVertex.push_back(v);
	v.p = ptVector[5]; m_vecVertex.push_back(v);
	v.p = ptVector[6]; m_vecVertex.push_back(v);
	v.p = ptVector[1]; m_vecVertex.push_back(v);
	v.p = ptVector[6]; m_vecVertex.push_back(v);
	v.p = ptVector[2]; m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = ptVector[4]; m_vecVertex.push_back(v);
	v.p = ptVector[0]; m_vecVertex.push_back(v);
	v.p = ptVector[3]; m_vecVertex.push_back(v);
	v.p = ptVector[4]; m_vecVertex.push_back(v);
	v.p = ptVector[3]; m_vecVertex.push_back(v);
	v.p = ptVector[7]; m_vecVertex.push_back(v);


}

void cCubePC::Update()
{
	//S
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

	//R
	D3DXMATRIXA16 matR, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotY);
	matR = matRY;

	//큐브 방향설정
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	//T
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	//m_matWorld에 S, R, T를 곱한다.
	m_matWorld = matS * matR * matT;

	//회전
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.017f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.017f;

	//이동
	if (GetKeyState('W') & 0x8000)
		m_vPosition = m_vPosition + (m_vDirection * MOVESPEED);
	if (GetKeyState('S') & 0x8000)
		m_vPosition = m_vPosition - (m_vDirection * MOVESPEED);

}

void cCubePC::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & cCubePC::GetPosition()
{
	return m_vPosition;
}
