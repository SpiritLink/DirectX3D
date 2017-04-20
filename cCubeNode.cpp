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
	//R == ȸ�� T == �̵� 
	//���� R
	D3DXMATRIXA16 matR, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotDeltaX);
	matR = matRY;

	//���� T
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(m_pParentWorldTransMatrix, m_vLocalPosition.x, m_vLocalPosition.y, m_vLocalPosition.z);

	//m_matWorld�� S, R, T�� ���Ѵ�.
	m_matLocalTransMatrix = matR * matT;

	//�ڽ��� R
	//�ڽ��� T
	//�θ� �̵��� �ڽ��� �̵��� ���ļ� ���ϸ� ���尡 �ȴ�.

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
