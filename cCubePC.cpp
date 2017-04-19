#include "stdafx.h"
#include "cCubePC.h"


cCubePC::cCubePC()
	: m_vDirection(0, 0, 1)	//���� ����
	, m_vPosition(0, 0, 0)	//��ġ
	, m_fRotY(0.0f)			//ȸ����
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	//�ﰢ�� �ϳ��� �׸��Բ� �ù��� ������
	ST_PC_VERTEX v;

	v.c = D3DCOLOR_XRGB(0, 255, 255);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 0.0f); m_vecVertex.push_back(v);

}

void cCubePC::Update()
{
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
