#include "stdafx.h"
#include "cLeftArm.h"


cLeftArm::cLeftArm()
{
}


cLeftArm::~cLeftArm()
{
}

void cLeftArm::Setup()
{
	cCubeNode::Setup();

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, -0.3f, -0.3f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPosition.y = 0.3f;
}