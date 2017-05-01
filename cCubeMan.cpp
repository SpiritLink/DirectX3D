#include "stdafx.h"
#include "cCubeMan.h"

#include "cHead.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"
#include "cGroup.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL),
	m_pTexture(NULL),
	m_pVertex(NULL),
	m_nType(0),
	m_nCurrentPoint(0),
	m_fT(0.0f)
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
	D3DXCreateTextureFromFile(g_pD3DDevice, "CubeMan.png", &m_pTexture);

	m_nType = nType;
	switch (nType)
	{
	case 1:
		m_vPosition = (*vecVertex)[0].p;
		m_nCurrentPoint = 0;
		break;
	case 2:
		m_vPosition = (*vecVertex)[0].p;
		m_nCurrentPoint = 1;
		break;
	}

	SetMaterial();

	cBody* pBody = new cBody;
	pBody->Setup();
	pBody->SetParentWorldTransMatrix(&m_matWorld);
	pBody->SetIdle(&m_bIsIdle);
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
	cCharacter::Update();
	if (m_pRoot)
		m_pRoot->Update();
	//if (m_pVecGroup)
		//CollisionCheck();
	if (m_nType == 1) MoveStraight();
	if (m_nType == 2) MoveCurve();
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

void cCubeMan::SetMaterial()
{
	ZeroMemory(&m_stMaterial, sizeof(D3DMATERIAL9));
	m_stMaterial.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMaterial.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_stMaterial.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_stMaterial.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}

void cCubeMan::CollisionCheck()
{
	D3DXVECTOR3 vPt1, vPt2, vPt3;

	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
		

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

			if (D3DXIntersectTri(&vPt1, &vPt2, &vPt3, &m_vRayPosition, &m_vRayDirection, &m_pU, &m_pV,
				&m_pDist))
			{
				float diffrence = 1000 - m_pDist + 1;
				if (fabs(m_vPosition.y - diffrence) < 2.0f)
				{
					m_vPosition.y = diffrence;
					return;
				}
			}
		}
	}
	m_vPosition.y = 1;
}

void cCubeMan::MoveStraight()
{
	int nextPoint = m_nCurrentPoint + 2;
	if (nextPoint > m_pVertex->size() - 1) nextPoint = 0;

	if (fabs(m_vPosition.x - (*m_pVertex)[nextPoint].p.x) < EPSILON &&
		fabs(m_vPosition.y - (*m_pVertex)[nextPoint].p.y) < EPSILON &&
		fabs(m_vPosition.z - (*m_pVertex)[nextPoint].p.z) < EPSILON)
	{
		m_nCurrentPoint += 2;
		nextPoint += 2;
		if (nextPoint > m_pVertex->size() - 1) nextPoint = 0;
		if (m_nCurrentPoint > m_pVertex->size() - 1) m_nCurrentPoint = 0;
	}

	D3DXVECTOR3 vDirection;

	vDirection = (*m_pVertex)[nextPoint].p - m_vPosition;
	D3DXVec3Normalize(&vDirection, &vDirection);

	m_vPosition = m_vPosition + (vDirection * 0.1f);
}
void cCubeMan::MoveCurve()
{
	int viaPoint = m_nCurrentPoint + 2;
	int nextPoint = viaPoint + 2;

	if (viaPoint > m_pVertex->size() - 1) viaPoint = 0;
	if (nextPoint > m_pVertex->size() - 1) nextPoint = 0;

	if (fabs(m_vPosition.x - (*m_pVertex)[nextPoint].p.x) < EPSILON &&
		fabs(m_vPosition.y - (*m_pVertex)[nextPoint].p.y) < EPSILON &&
		fabs(m_vPosition.z - (*m_pVertex)[nextPoint].p.z) < EPSILON)
	{
		m_fT = 0.0f;
		m_nCurrentPoint += 4;
		if (viaPoint > m_pVertex->size() - 1) viaPoint = 0;
		if (nextPoint > m_pVertex->size() - 1) nextPoint = 0;
		if (m_nCurrentPoint > m_pVertex->size() - 1) m_nCurrentPoint = 0;
	}

	m_fT += 0.005f;
	D3DXVECTOR3 P0, P1, P2;
	D3DXVECTOR3 StartPt, EndPt;
	D3DXVECTOR3 toVia, toEnd, vDirection;

	P0 = (*m_pVertex)[m_nCurrentPoint].p;
	P1 = (*m_pVertex)[viaPoint].p;
	P2 = (*m_pVertex)[nextPoint].p;

	toVia = P1 - P0;
	toEnd = P2 - P1;

	StartPt = P0 + (toVia * m_fT);
	EndPt = P1 + (toEnd * m_fT);

	vDirection = EndPt - StartPt;
	m_vPosition = StartPt + (vDirection * m_fT);

	
}
