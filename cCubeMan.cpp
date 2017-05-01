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
	m_pVecGroup(NULL),
	m_pU(0.0f),
	m_pV(0.0f),
	m_pDist(0.0f)
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
	cCharacter::Update();
	if (m_pRoot)
		m_pRoot->Update();
	if (m_pVecGroup)
		CollisionCheck();
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
	D3DXVECTOR3 vTemp1, vTemp2, vTemp3;
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	
	D3DXVECTOR4 vTemp4, vTemp5, vTemp6;
	

	for (int i = 0; i < (*m_pVecGroup).size(); ++i)
	{
		for (int j = 0; j < (*m_pVecGroup)[i]->GetVertex().size(); j += 3)	//점들을 3개씩 확인
		{
			vTemp1 = (*m_pVecGroup)[i]->GetVertex()[j + 0].p;
			vTemp2 = (*m_pVecGroup)[i]->GetVertex()[j + 1].p;
			vTemp3 = (*m_pVecGroup)[i]->GetVertex()[j + 2].p;

			D3DXVec3TransformCoord(&vTemp1, &vTemp1, &matWorld);
			D3DXVec3TransformCoord(&vTemp2, &vTemp2, &matWorld);
			D3DXVec3TransformCoord(&vTemp3, &vTemp3, &matWorld);

			if (D3DXIntersectTri(&vTemp1, &vTemp2, &vTemp3, &m_vRayPosition, &m_vRayDirection, &m_pU, &m_pV,
				&m_pDist))
			{
				float diffrence = 1000 - m_pDist + 1;
				if (fabs(m_vPosition.y - diffrence) < 0.5f)
				{
					m_vPosition.y = diffrence;
					return;
				}
				else
				{
					m_vPosition = m_vPosition + (m_vDirection * 0.1f);
					return;
				}
			}
		}
	}
	m_vPosition.y = 1;
}
