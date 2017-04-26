#include "stdafx.h"
#include "cCubeMan.h"

#include "cHead.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL),
	m_pTexture(NULL),
	m_pVertex(NULL),
	m_nType(0)
{
}


cCubeMan::~cCubeMan()
{
	if (m_pRoot)
		m_pRoot->Destroy();
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pVertex);
}

void cCubeMan::Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType)
{
	cCharacter::Setup(vecVertex,nType);
	m_pVertex = vecVertex;
	if (nType == 1)
	{
		m_vPosition = (*vecVertex)[0].p;
		m_nVecCnt = 1;
		m_vNextPoint = (*vecVertex)[1].p;
	}
	
	if (nType == 2)
	{
		m_vPosition = (*vecVertex)[2].p;
		m_nVecCnt = 3;
		m_vNextPoint = (*vecVertex)[3].p;
	}
	m_nType = nType;

	D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
	D3DXCreateTextureFromFile(g_pD3DDevice, "CubeMan.png", &m_pTexture);

	SetMaterial();

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTransMatrix(&m_matWorld);
	pBody->SetIdle(&m_pIsIdle);
	m_pRoot = pBody;

	cHead* pHead = new cHead;
	pHead->Setup();
	m_pRoot->AddChild(pHead);

	cLeftArm* pLeftArm = new cLeftArm;
	pLeftArm->Setup();
	m_pRoot->AddChild(pLeftArm);

	cRightArm* pRightArm = new cRightArm;
	pRightArm->Setup();
	m_pRoot->AddChild(pRightArm);

	cLeftLeg* pLeftLeg = new cLeftLeg;
	pLeftLeg->Setup();
	m_pRoot->AddChild(pLeftLeg);

	cRightLeg* pRightLeg = new cRightLeg;
	pRightLeg->Setup();
	m_pRoot->AddChild(pRightLeg);

}

void cCubeMan::Update()
{
	if (m_nType == 1) MoveStraight();
	if (m_nType == 2) MoveCurve();
	cCharacter::Update();
	if (m_pRoot)
		m_pRoot->Update();
}

void cCubeMan::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetMaterial(&m_stMaterial);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	cCharacter::Render();

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if (m_pRoot)
		m_pRoot->Render();

	g_pD3DDevice->SetTexture(0, 0);
}

void cCubeMan::MoveStraight()
{
	if (fabs(m_vPosition.x - m_vNextPoint.x) < EPSILON &&	///x, y, z 의 좌표가 다음 지점까지 도착했는지 확인합니다.
		fabs(m_vPosition.y - m_vNextPoint.y) < EPSILON &&
		fabs(m_vPosition.z - m_vNextPoint.z) < EPSILON)
	{
		if (m_nVecCnt + 2 < m_pVertex->size())
		{
			m_nVecCnt += 2;
			m_vNextPoint = (*m_pVertex)[m_nVecCnt].p;
			D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
		}
		else
		{
			m_nVecCnt = 1;
			m_vNextPoint = (*m_pVertex)[m_nVecCnt].p;
			D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
		}
	}
	m_vPosition = m_vPosition + m_vDirection * 0.1f;
}

void cCubeMan::MoveCurve()
{
	if (fabs(m_vPosition.x - m_vNextPoint.x) < EPSILON &&	///x, y, z 의 좌표가 다음 지점까지 도착했는지 확인합니다.
		fabs(m_vPosition.y - m_vNextPoint.y) < EPSILON &&
		fabs(m_vPosition.z - m_vNextPoint.z) < EPSILON)
	{
		if (m_nVecCnt + 2 < m_pVertex->size())
		{
			m_nVecCnt += 2;
			m_vNextPoint = (*m_pVertex)[m_nVecCnt].p;
			D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
		}
		else
		{
			m_nVecCnt = 2;
			m_vNextPoint = (*m_pVertex)[m_nVecCnt].p;
			D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
		}
	}
	m_vPosition = m_vPosition + m_vDirection * 0.1f;

}
void cCubeMan::SetMaterial()
{
	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));
	m_stMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMaterial.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_stMaterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

