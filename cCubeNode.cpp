#include "stdafx.h"
#include "cCubeNode.h"


cCubeNode::cCubeNode()
	: m_fRotDeltaX(0.0f) ,
	m_pParentWorldTransMatrix(NULL),
	m_vLocalPosition(0, 0, 0),
	m_bMoveDirection(false)
{
	D3DXMatrixIdentity(&m_matLocalTransMatrix);
	D3DXMatrixIdentity(&m_matWorldTransMatrix);
	D3DXMatrixIdentity(&m_matR);
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
	UpdateDeltaX();
	D3DXMATRIXA16 matT;

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT,	m_vLocalPosition.x, 
									m_vLocalPosition.y, 
									m_vLocalPosition.z);

	m_matLocalTransMatrix = m_matR * matT;

	m_matWorldTransMatrix = m_matLocalTransMatrix;

	if (m_pParentWorldTransMatrix)
		m_matWorldTransMatrix *= *m_pParentWorldTransMatrix;

	for each(auto p in m_vecChild)
	{
		p->Update();
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

void cCubeNode::UpdateDeltaX()
{
	if (*m_bIsIdle)
	{
		//Idle 상태일때
		if (abs(m_fRotDeltaX) < 0.1f) m_fRotDeltaX = 0;
		
		if (m_fRotDeltaX > 0) m_fRotDeltaX -= 0.1f;
		if (m_fRotDeltaX < 0) m_fRotDeltaX += 0.1f;
	}
	else
	{
		//움직이는 상태일때
		if (m_bMoveDirection)
		{
			m_fRotDeltaX -= 0.1f;
			if (m_fRotDeltaX < -0.6f) m_bMoveDirection = false;
		}
		else
		{
			m_fRotDeltaX += 0.1f;
			if (m_fRotDeltaX > 0.6f) m_bMoveDirection = true;
		}
		
	}
}


cCubeNode::~cCubeNode()
{
}
