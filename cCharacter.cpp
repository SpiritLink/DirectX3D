#include "stdafx.h"
#include "cCharacter.h"
#include "cGroup.h"

cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(-5, 1, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCharacter::~cCharacter()
{
}

void cCharacter::Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType)
{
	//
}

void cCharacter::Update(iMap* pMap)
{
	D3DXVECTOR3 vPosition = m_vPosition;
	m_pMap = pMap;

	if (GetKeyState('S') & 0x8000)
	{
		vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (GetKeyState('W') & 0x8000)
	{
		vPosition = m_vPosition - (m_vDirection * 0.1f);
	}
	if (GetKeyState('A') & 0x8000)
	{
		m_fRotY -= 0.01f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fRotY += 0.01f;
	}


	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

	//Rotate
	D3DXMATRIXA16 matR, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotY);
	matR = matRY;

	//방향 설정
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
		{
			m_vPosition = vPosition;
		}
	}

	//Translate
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y + 1.0f, m_vPosition.z);

	m_matWorld = matS * matR * matT;
}


void cCharacter::Render()
{
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
