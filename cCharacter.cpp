#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(0, 0, 0),
	m_pIsIdle(true),
	m_vRayPosition(0, 1000, 0),
	m_vRayDirection(0, -1, 0)
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

void cCharacter::Update()
{
	m_pIsIdle = true;
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.017f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.017f;
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + m_vDirection * 0.1f;
		m_pIsIdle = false;
	}
	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - m_vDirection * 0.1f;
		m_pIsIdle = false;
	}

	m_vRayPosition.x = m_vPosition.x;
	m_vRayPosition.y = 1000;
	m_vRayPosition.z = m_vPosition.z;

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);

	//Rotate
	D3DXMATRIXA16 matR, matRY;
	D3DXMatrixRotationY(&matRY, m_fRotY);
	matR = matRY;

	//���� ����
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	//Translate
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS * matR * matT;
}

void cCharacter::Render()
{
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
