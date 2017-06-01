#include "stdafx.h"
#include "cFrustum.h"
#include "cCamera.h"

cFrustum::cFrustum()
{
}


cFrustum::~cFrustum()
{
}

void cFrustum::Setup()
{
	// : 1. 상자 만들기 위한 정점 8 설정
	// : 2. 초기화
	// : near
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));	//
	m_vecProjVertex.push_back(D3DXVECTOR3(-1,  1, 0));	//
	m_vecProjVertex.push_back(D3DXVECTOR3( 1,  1, 0));	//
	m_vecProjVertex.push_back(D3DXVECTOR3( 1, -1, 0));	//
	
	// : far 
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));	//
	m_vecProjVertex.push_back(D3DXVECTOR3(-1,  1, 1));	//
	m_vecProjVertex.push_back(D3DXVECTOR3( 1,  1, 1));	//
	m_vecProjVertex.push_back(D3DXVECTOR3( 1, -1, 1));	//

	m_vecPlane.resize(6);
	m_vecWorldVertex.resize(8);
}

void cFrustum::Update()
{
	// : 1. viewMatrix, Projection 구하기(getTransForm);
	D3DXMATRIXA16 matView,matProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);				/// 뷰행렬을 얻어옵니다.
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);	/// 프로젝션 행렬을 얻어옵니다.
	
	// : 2. D3DXVec3Unproject(1. 변환된 월드 버텍스, 프로젝션 버텍스, 뷰포트 (NULL로 넣음), 프로젝션 매트릭스, 뷰매트릭스, 월드매트릭스(NULL로 넣음)) 구해낸다.
	for (size_t i = 0; i < m_vecProjVertex.size(); ++i)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProjection, &matView, NULL);
	}

	// : 3. 면을 생성한다. D3DXPlaneFromPoints() [점을 이용해서 면을 생성] 각 정점 3개가 순차적으로 들어감 (그리기 순서가 굉장히 중요함)
	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);	/// front
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[7], &m_vecWorldVertex[6], &m_vecWorldVertex[5]);	/// far
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5], &m_vecWorldVertex[6]);	/// top
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[4], &m_vecWorldVertex[0], &m_vecWorldVertex[3]);	/// bottom
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[4], &m_vecWorldVertex[5], &m_vecWorldVertex[1]);	/// left
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[3], &m_vecWorldVertex[2], &m_vecWorldVertex[6]);	/// right

}

bool cFrustum::IsIn(ST_SPHERE * pSphere)
{
	/// 각 면에 loop
	// 안에 있는지 밖에 있는지 걸쳐 있는지 검사한다.
	// D3DXPlaneDotCoord (면, 정점) -> 숫자(거리)가 나옴 [d값] (면과 점사이의 거리를 계산하는 함수) 

	for (size_t i = 0; i < m_vecPlane.size(); ++i)
	{
		if (D3DXPlaneDotCoord(&m_vecPlane[i], &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}

	return true;
}
