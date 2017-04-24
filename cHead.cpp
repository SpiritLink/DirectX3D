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

	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		switch (i)
		{
		case 0:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 0, 8, 5, 15); break;
		case 6:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 6, 8, 17, 15); break;
		case 12:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 18, 8, 31, 15); break;
		case 18:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 18, 8, 31, 15); break;
		case 24:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 16, 0, 23, 7); break;
		case 30:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 8, 0, 15, 7); break;
		}
	}

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}

	m_vLocalPosition.y = 0.5f;

}

void cHead::Update()
{
	D3DXMatrixIdentity(&m_matR);
	D3DXMatrixRotationY(&m_matR, GetRotateDeltaX());//헤드랑 바디는 회전 않하도록
	cCubeNode::Update();
}

void cHead::UpdateDeltaX()
{
	if (*GetIdle())
	{
		//Idle 상태일때
		if (m_bMoveDirection)
		{
			SetRotateDeltaX(GetRotateDeltaX() - 0.05f);
			if (GetRotateDeltaX() < -0.6f) m_bMoveDirection = false;
		}
		else
		{
			SetRotateDeltaX(GetRotateDeltaX() + 0.05f);
			if (GetRotateDeltaX() > 0.6f) m_bMoveDirection = true;
		}
	}
	else
	{
		if (abs(GetRotateDeltaX()) < 0.1f) SetRotateDeltaX(0.0f);

		if (GetRotateDeltaX() > 0) SetRotateDeltaX(GetRotateDeltaX() - 0.05f);
		if (GetRotateDeltaX() < 0) SetRotateDeltaX(GetRotateDeltaX() + 0.05f);
	}
}
