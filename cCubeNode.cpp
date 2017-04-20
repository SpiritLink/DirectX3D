#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	:m_vLocalPosition(0,0,0)
	, m_fRotDeltaX(0.0f)
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
	////R == ȸ�� T == �̵� 
	////���� R
	D3DXMATRIXA16 matR, matRX;
	D3DXMatrixRotationX(&matRX, m_fRotDeltaX);
	matR = matRX;

	//���� T
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vLocalPosition.x, m_vLocalPosition.y, m_vLocalPosition.z);

	//m_matWorld�� S, R, T�� ���Ѵ�.
	m_matLocalTransMatrix = matR * matT;

	////�ڽ��� R
	////�ڽ��� T
	////�θ� �̵��� �ڽ��� �̵��� ���ļ� ���ϸ� ���尡 �ȴ�.

	m_matWorldTransMatrix = m_matLocalTransMatrix * (*m_pParentWorldTransMatrix);

	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->SetParentWorldTransMatrix(&m_matWorldTransMatrix);
		m_vecChild[i]->Update();
	}

	//D3DXMATRIXA16 mat;
	//D3DXMatrixIsIdentity(&mat);
	//for (int i = 0; i < m_vecChild.size(); ++i)
	//{

	//	D3DXMatrixTranslation(&mat, m_vecChild[i]->m_vLocalPosition.x, m_vecChild[i]->m_vLocalPosition.y, m_vecChild[i]->m_vLocalPosition.z);
	//	m_vecChild[i]->m_matLocalTransMatrix = mat;

	//	m_vecChild[i]->m_matWorldTransMatrix = m_vecChild[i]->m_matLocalTransMatrix * (*m_pParentWorldTransMatrix);
	//}
}

void cCubeNode::Render()
{
	if (m_vecVertex.size() > 0)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTransMatrix);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PNT_VERTEX));

	}

	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Render();
	}
}


cCubeNode::~cCubeNode()
{
}
