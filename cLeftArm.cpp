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

	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		switch (i)
		{
		case 0:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 40, 16, 44, 32); break;	//전면
		case 6:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 40, 16, 44, 32); break;	//후면
		case 12:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 44, 16, 48, 32); break;	//좌면
		case 18:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 44, 16, 48, 32); break;	//우면
		case 24:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 8, 0, 16, 8); break;	//상단
		case 30:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 16, 0, 24, 8); break;	//하단
		}
	}

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

void cLeftArm::Update()
{
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixRotationX(&m_matR, GetRotateDeltaX());//헤드랑 바디는 회전 않하도록
	cCubeNode::Update();
}
