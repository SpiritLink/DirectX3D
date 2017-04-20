#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	:m_vLocalPosition(0,0,0)
{
	D3DXMatrixIdentity(&m_matLocalTransMatrix);
	D3DXMatrixIdentity(&m_matWorldTransMatrix);
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		delete m_vecChild[i];
	}
	m_vecChild.clear();
}

void cCubeNode::Setup()
{
	cCubePNT::Setup();
}

void cCubeNode::Update()
{
	//R == 회전 T == 이동 
	//로컬 R
	D3DXMATRIXA16 matR, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotDeltaX);
	matR = matRY;

	//로컬 T
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(m_pParentWorldTransMatrix, m_vLocalPosition.x, m_vLocalPosition.y, m_vLocalPosition.z);

	//m_matWorld에 S, R, T를 곱한다.
	m_matLocalTransMatrix = matR * matT;

	//자신의 R
	//자신의 T
	//부모 이동과 자신의 이동을 합쳐서 곱하면 월드가 된다.

	m_matWorldTransMatrix = m_matLocalTransMatrix * *m_pParentWorldTransMatrix;

	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->SetParentWorldTransMatrix(&m_matWorldTransMatrix);
		m_vecChild[i]->Update();
	}
}

void cCubeNode::Render()
{
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_vecChild[i]->m_matWorldTransMatrix);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecChild[i]->m_vecVertex.size() / 3,
			&m_vecChild[i]->m_vecVertex[0],
			sizeof(ST_PNT_VERTEX));
	}
}


cCubeNode::~cCubeNode()
{
}
