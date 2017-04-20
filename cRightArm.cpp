#include "stdafx.h"
#include "cRightArm.h"


cRightArm::cRightArm()
{
}


cRightArm::~cRightArm()
{
}

void cRightArm::Setup()
{
	cCubeNode::Setup();
	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i].p.z *= 0.25f;
		m_vecVertex[i].p.x *= 0.25f;
		m_vecVertex[i].p.y *= 0.75f;
		m_vecVertex[i].p += D3DXVECTOR3(1.0f, 2.25f, 0);
		D3DXVec3Scale(&m_vecVertex[i].p, &m_vecVertex[i].p, 0.25f);
	}
}