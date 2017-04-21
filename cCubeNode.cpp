#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	:	m_fRotDeltaX(0.0f)
	,	m_pParentWorldTransMatrix(NULL),
		m_vLocalPosition(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matLocalTransMatrix);
	D3DXMatrixIdentity(&m_matWorldTransMatrix);
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	pChild->m_pParentWorldTransMatrix = &m_matWorldTransMatrix;
	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
	for each(auto p in m_vecChild)
	{
		p->Destroy();
	}
	delete this;
}

void cCubeNode::Setup()
{
	cCubePNT::Setup();
}

void cCubeNode::Update()
{
	cCubePNT::Update();

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationX(&matR, m_fRotDeltaX);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,	m_vLocalPosition.x, 
									m_vLocalPosition.y, 
									m_vLocalPosition.z);

	m_matLocalTransMatrix = matR * matT;

	m_matWorldTransMatrix = m_matLocalTransMatrix;

	if (m_pParentWorldTransMatrix)
		m_matWorldTransMatrix *= *m_pParentWorldTransMatrix;

	for each(auto p in m_vecChild)
	{
		p->Update();
		p->SetRotateDeltaX(p->GetRotateDeltaX() + 0.1f);
	}
}

void cCubeNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTransMatrix);

	cCubePNT::Render();
	for each(auto p in m_vecChild)
	{
		p->Render();
	}
}


cCubeNode::~cCubeNode()
{
}
