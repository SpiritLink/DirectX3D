#include "stdafx.h"
#include "cCharacter.h"
#include "cGroup.h"

cCharacter::cCharacter()
	: m_fRotY(0.0f),
	m_vDirection(0, 0, 1),
	m_vPosition(-5, 1, 0),
	m_bIsIdle(true),
	m_vRayPosition(0, 1000, 0),
	m_vRayDirection(0, -1, 0),
	m_pVecGroup(NULL),
	m_pU(0.0f),
	m_pV(0.0f),
	m_pDist(0.0f)
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
	m_bIsIdle = true;

	m_vRayPosition.x = m_vPosition.x;
	m_vRayPosition.y = 1000;
	m_vRayPosition.z = m_vPosition.z;

	moveCheck();

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

	//Translate
	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matS * matR * matT;
}


void cCharacter::moveCheck()
{
	D3DXVECTOR3 vTempRayPt;
	vTempRayPt = m_vRayPosition;

	D3DXVECTOR3 vPt1, vPt2, vPt3;

	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;

	float tempDist;


	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.017f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.017f;

	if (!m_pVecGroup)
		return;

	if (GetKeyState('W') & 0x8000)
	{
		vTempRayPt = m_vRayPosition - m_vDirection * 0.1f;
		m_bIsIdle = false;
		for (int i = 0; i < (*m_pVecGroup).size(); ++i)
		{
			for (int j = 0; j < (*m_pVecGroup)[i]->GetVertex().size(); j += 3)	//점들을 3개씩 확인
			{
				vPt1 = (*m_pVecGroup)[i]->GetVertex()[j + 0].p;
				vPt2 = (*m_pVecGroup)[i]->GetVertex()[j + 1].p;
				vPt3 = (*m_pVecGroup)[i]->GetVertex()[j + 2].p;

				D3DXVec3TransformCoord(&vPt1, &vPt1, &matWorld);
				D3DXVec3TransformCoord(&vPt2, &vPt2, &matWorld);
				D3DXVec3TransformCoord(&vPt3, &vPt3, &matWorld);

				if (D3DXIntersectTri(&vPt1, &vPt2, &vPt3, &vTempRayPt, &m_vRayDirection, &m_pU, &m_pV,
					&tempDist))
				{
					float diffrence = 1000 - tempDist + 1;
					if (fabs(m_vPosition.y - diffrence) < 0.5f && m_vRayPosition != vTempRayPt)
					{
						m_vPosition = m_vPosition - (m_vDirection * 0.1f);
						return;
					}
				}
			}
		}

	}
	if (GetKeyState('S') & 0x8000)
	{
		vTempRayPt = m_vRayPosition + m_vDirection * 0.1f;
		m_bIsIdle = false;

		for (int i = 0; i < (*m_pVecGroup).size(); ++i)
		{
			for (int j = 0; j < (*m_pVecGroup)[i]->GetVertex().size(); j += 3)	//점들을 3개씩 확인
			{
				vPt1 = (*m_pVecGroup)[i]->GetVertex()[j + 0].p;
				vPt2 = (*m_pVecGroup)[i]->GetVertex()[j + 1].p;
				vPt3 = (*m_pVecGroup)[i]->GetVertex()[j + 2].p;

				D3DXVec3TransformCoord(&vPt1, &vPt1, &matWorld);
				D3DXVec3TransformCoord(&vPt2, &vPt2, &matWorld);
				D3DXVec3TransformCoord(&vPt3, &vPt3, &matWorld);

				if (D3DXIntersectTri(&vPt1, &vPt2, &vPt3, &vTempRayPt, &m_vRayDirection, &m_pU, &m_pV,
					&tempDist))
				{
					float diffrence = 1000 - tempDist + 1;
					if (fabs(m_vPosition.y - diffrence) < 0.5f && m_vRayPosition != vTempRayPt)
					{
						m_vPosition = m_vPosition + (m_vDirection * 0.1f);
						return;
					}
				}
			}
		}


	}



}

void cCharacter::Render()
{
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
