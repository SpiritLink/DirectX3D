#include "stdafx.h"
#include "cRightLeg.h"


cRightLeg::cRightLeg()
{
}


cRightLeg::~cRightLeg()
{
}

void cRightLeg::Setup()
{
	cCubeNode::Setup();
	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].p.x *= 0.5f;
		m_vecVertex[i].p.y *= 2.0f;
		m_vecVertex[i].p += D3DXVECTOR3(1, 2.0f, 0);
		D3DXVec3Scale(&m_vecVertex[i].p, &m_vecVertex[i].p, 0.125f);
	}
}