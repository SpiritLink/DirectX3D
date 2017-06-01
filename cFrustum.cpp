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
	std::vector<D3DXVECTOR3> vecVertex;
	vecVertex.push_back(D3DXVECTOR3(-1, 1, 1));		//1
	vecVertex.push_back(D3DXVECTOR3(1, 1, 1));		//2
	vecVertex.push_back(D3DXVECTOR3(1, 1, 0));		//3
	vecVertex.push_back(D3DXVECTOR3(-1, 1, 0));		//4

	vecVertex.push_back(D3DXVECTOR3(-1, -1, 1));		//5
	vecVertex.push_back(D3DXVECTOR3(1, -1, 1));		//6
	vecVertex.push_back(D3DXVECTOR3(1, -1, 0));		//7
	vecVertex.push_back(D3DXVECTOR3(-1, -1, 0));		//8
	// : 1. 상자 만들기 위한 정점 8 설정



	// : 2. 초기화
	m_vecProjVertex = vecVertex;
	m_vecWorldVertex = vecVertex;
	for (int i = 0; i < 6; ++i)
	{
		m_vecPlane.push_back(D3DXPLANE());
	}
}

void cFrustum::Update()
{
	// : 1. viewMatrix, Projection 구하기(getTransForm);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProjection;
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);	/// 프로젝션 행렬을 얻어옵니다.
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);				/// 월드 행렬을 얻어옵니다.

	//for (size_t i = 0; i < m_vecProjVertex.size(); ++i)
	//{
	//	D3DXVec3TransformCoord(&m_vecProjVertex[i], &m_vecProjVertex[i], &matView);			/// 월드 버텍스 변환
	//	D3DXVec3TransformCoord(&m_vecWorldVertex[i], &m_vecWorldVertex[i], &matWorld);		/// 프로젝션 버텍스 변환
	//}
	
	// : 2. D3DXVec3Unproject(1. 변환된 월드 버텍스, 프로젝션 버텍스, 뷰포트 (NULL로 넣음), 프로젝션 매트릭스, 뷰매트릭스, 월드매트릭스(NULL로 넣음)) 구해낸다.
	for (size_t i = 0; i < m_vecProjVertex.size(); ++i)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProjection, &matView, NULL);
	}

	// : 3. 면을 생성한다. D3DXPlaneFromPoints() [점을 이용해서 면을 생성] 각 정점 3개가 순차적으로 들어감 (그리기 순서가 굉장히 중요함)
	D3DXPlaneFromPoints(&m_vecPlane[0] , &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5]);
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[7], &m_vecWorldVertex[6], &m_vecWorldVertex[5]);
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[0], &m_vecWorldVertex[3], &m_vecWorldVertex[7]);
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[3], &m_vecWorldVertex[2], &m_vecWorldVertex[7]);
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[1], &m_vecWorldVertex[0], &m_vecWorldVertex[5]);

}

bool cFrustum::IsIn(ST_SPHERE * pSphere)
{
	/// 각 면에 loop
	// 안에 있는지 밖에 있는지 걸쳐 있는지 검사한다.
	// D3DXPlaneDotCoord (면, 정점) -> 숫자(거리)가 나옴 [d값] (면과 점사이의 거리를 계산하는 함수) 

	for (size_t i = 0; i < m_vecPlane.size(); ++i)
	{
		D3DXVECTOR3 center = pSphere->vCenter;
		float Result = D3DXPlaneDotCoord(&m_vecPlane[i], &center);

		if (Result > 0)
		{
			return false;	/// 뒤쪽 공간에 존재한다.
		}
	}

	return true;
}
