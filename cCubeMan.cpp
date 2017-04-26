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
	m_nType(0),
	m_nViaCnt(0),
	m_nNextCnt(0)
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
		m_nBeforeCnt = 1;
		m_vNextPoint = (*vecVertex)[1].p;
	}
	
	if (nType == 2)
	{
		m_vPosition = (*vecVertex)[0].p;
		m_nBeforeCnt = 0;
		m_nViaCnt = 1;
		m_nNextCnt = 3;
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
		if (m_nBeforeCnt + 2 < m_pVertex->size())
		{
			m_nBeforeCnt += 2;
			m_vNextPoint = (*m_pVertex)[m_nBeforeCnt].p;
			D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
		}
		else
		{
			m_nBeforeCnt = 1;
			m_vNextPoint = (*m_pVertex)[m_nBeforeCnt].p;
			D3DXVec3Normalize(&m_vDirection, &(m_vNextPoint - m_vPosition));
		}
	}
	m_vPosition = m_vPosition + m_vDirection * 0.1f;
}

void cCubeMan::MoveCurve()
{
	D3DXVECTOR3 BeforePt, ViaPt, NextPt;	//출발점, 경유점, 도착점 생성
	D3DXVECTOR3 StartPt, EndPt;				//방향 계산에 사용할 두점 생성
	D3DXVECTOR3 ScaleX, ScaleZ;				//스케일한 벡터를 가지고 있을 벡터
	float fScaleX, fScaleZ;
	BeforePt = (*m_pVertex)[m_nBeforeCnt].p;	//출발점
	ViaPt = (*m_pVertex)[m_nViaCnt].p;			//경유점
	NextPt = (*m_pVertex)[m_nNextCnt].p;		//도착점

	///첫번째 선에서 움직인 거리를 구한다. (X축에서 움직인 거리)
	if (m_vPosition.x - BeforePt.x == 0) 
		fScaleX = 0;
	else
		fScaleX = (m_vPosition.x - BeforePt.x) / (ViaPt.x - BeforePt.x);	///X축의 움직인 비율을 구합니다.
	
	D3DXVec3Scale(&ScaleX, &BeforePt, fScaleX);	/// 비율만큼 이동한 좌표를 구합니다.(m_vPosition과 다르기 때문에)
	StartPt = BeforePt + ScaleX;				/// 각도를 구할 출발점을 구합니다.

	if (m_vPosition.z - NextPt.z == 0)
		fScaleZ = 0;
	else
		fScaleZ = 1 - ((m_vPosition.z - ViaPt.z) / (m_vPosition.z - ViaPt.z));	///Z축의 움직인 비율을 구합니다.

	D3DXVec3Scale(&ScaleZ, &ViaPt, fScaleZ);	/// 비율만큼 이동한 좌표를 구합니다.(m_vPosition과 다르기 때문에)
	EndPt = ViaPt + ScaleZ;						/// 각도를 구할 도착점을 구합니다.

		D3DXVec3Normalize(&m_vDirection, &(EndPt - StartPt));

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

