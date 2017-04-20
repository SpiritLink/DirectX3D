#include "stdafx.h"
#include "cHead.h"


cHead::cHead()
{
}


cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();
	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].p.z *= 0.5f;
		m_vecVertex[i].p.x *= 0.5f;
		m_vecVertex[i].p.y *= 0.5f;
		m_vecVertex[i].p += D3DXVECTOR3(0, 3.5f, 0);
		D3DXVec3Scale(&m_vecVertex[i].p, &m_vecVertex[i].p, 0.25f);
	}
	
}