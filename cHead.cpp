#include "stdafx.h"
#include "cHead.h"
#define XBLOCK 0.125f
#define YBLOCK 0.256f

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
		case 0:
			m_vecVertex[i + 0].t = D3DXVECTOR2(XBLOCK, YBLOCK * 2.0f);
			m_vecVertex[i + 1].t = D3DXVECTOR2(XBLOCK, YBLOCK);
			m_vecVertex[i + 2].t = D3DXVECTOR2(XBLOCK * 2.0f, YBLOCK);
			m_vecVertex[i + 3].t = D3DXVECTOR2(XBLOCK, YBLOCK * 2.0f);
			m_vecVertex[i + 4].t = D3DXVECTOR2(XBLOCK * 2.0f, YBLOCK);
			m_vecVertex[i + 5].t = D3DXVECTOR2(XBLOCK * 2.0f, YBLOCK * 2.0f);
			break;
		case 6:
			m_vecVertex[i + 0].t = D3DXVECTOR2(XBLOCK * 3.0f, YBLOCK * 2.0f);
			m_vecVertex[i + 1].t = D3DXVECTOR2(XBLOCK * 3.0f, YBLOCK);
			m_vecVertex[i + 2].t = D3DXVECTOR2(XBLOCK * 4.0f, YBLOCK);
			m_vecVertex[i + 3].t = D3DXVECTOR2(XBLOCK * 3.0f, YBLOCK * 2.0f);
			m_vecVertex[i + 4].t = D3DXVECTOR2(XBLOCK * 4.0f, YBLOCK);
			m_vecVertex[i + 5].t = D3DXVECTOR2(XBLOCK * 4.0f, YBLOCK * 2.0f);
			break;
		case 12:
			m_vecVertex[i + 0].t = D3DXVECTOR2(XBLOCK * 0, YBLOCK * 2);
			m_vecVertex[i + 1].t = D3DXVECTOR2(XBLOCK * 0, YBLOCK * 1);
			m_vecVertex[i + 2].t = D3DXVECTOR2(XBLOCK * 1, YBLOCK * 1);
			m_vecVertex[i + 3].t = D3DXVECTOR2(XBLOCK * 0, YBLOCK * 2);
			m_vecVertex[i + 4].t = D3DXVECTOR2(XBLOCK * 1, YBLOCK * 1);
			m_vecVertex[i + 5].t = D3DXVECTOR2(XBLOCK * 2, YBLOCK * 1);
			break;
		case 18:
			m_vecVertex[i + 0].t = D3DXVECTOR2(XBLOCK * 2, YBLOCK * 2);
			m_vecVertex[i + 1].t = D3DXVECTOR2(XBLOCK * 2, YBLOCK * 1);
			m_vecVertex[i + 2].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 1);
			m_vecVertex[i + 3].t = D3DXVECTOR2(XBLOCK * 2, YBLOCK * 2);
			m_vecVertex[i + 4].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 1);
			m_vecVertex[i + 5].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 2);
			break;
		case 24:
			m_vecVertex[i + 0].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 2);
			m_vecVertex[i + 1].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 1);
			m_vecVertex[i + 2].t = D3DXVECTOR2(XBLOCK * 4, YBLOCK * 1);
			m_vecVertex[i + 3].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 2);
			m_vecVertex[i + 4].t = D3DXVECTOR2(XBLOCK * 4, YBLOCK * 1);
			m_vecVertex[i + 5].t = D3DXVECTOR2(XBLOCK * 4, YBLOCK * 2);
			break;
		case 30:
			m_vecVertex[i + 0].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 2);
			m_vecVertex[i + 1].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 1);
			m_vecVertex[i + 2].t = D3DXVECTOR2(XBLOCK * 4, YBLOCK * 1);
			m_vecVertex[i + 3].t = D3DXVECTOR2(XBLOCK * 3, YBLOCK * 2);
			m_vecVertex[i + 4].t = D3DXVECTOR2(XBLOCK * 4, YBLOCK * 1);
			m_vecVertex[i + 5].t = D3DXVECTOR2(XBLOCK * 4, YBLOCK * 2);
			break;

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
