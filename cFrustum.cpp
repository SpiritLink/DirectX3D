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
	// : 1. ���� ����� ���� ���� 8 ����
	// : 2. �ʱ�ȭ
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
	// : 1. viewMatrix, Projection ���ϱ�(getTransForm);
	D3DXMATRIXA16 matView,matProjection;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);				/// ������� ���ɴϴ�.
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);	/// �������� ����� ���ɴϴ�.
	
	// : 2. D3DXVec3Unproject(1. ��ȯ�� ���� ���ؽ�, �������� ���ؽ�, ����Ʈ (NULL�� ����), �������� ��Ʈ����, ���Ʈ����, �����Ʈ����(NULL�� ����)) ���س���.
	for (size_t i = 0; i < m_vecProjVertex.size(); ++i)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProjection, &matView, NULL);
	}

	// : 3. ���� �����Ѵ�. D3DXPlaneFromPoints() [���� �̿��ؼ� ���� ����] �� ���� 3���� ���������� �� (�׸��� ������ ������ �߿���)
	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);	/// front
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[7], &m_vecWorldVertex[6], &m_vecWorldVertex[5]);	/// far
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5], &m_vecWorldVertex[6]);	/// top
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[4], &m_vecWorldVertex[0], &m_vecWorldVertex[3]);	/// bottom
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[4], &m_vecWorldVertex[5], &m_vecWorldVertex[1]);	/// left
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[3], &m_vecWorldVertex[2], &m_vecWorldVertex[6]);	/// right

}

bool cFrustum::IsIn(ST_SPHERE * pSphere)
{
	/// �� �鿡 loop
	// �ȿ� �ִ��� �ۿ� �ִ��� ���� �ִ��� �˻��Ѵ�.
	// D3DXPlaneDotCoord (��, ����) -> ����(�Ÿ�)�� ���� [d��] (��� �������� �Ÿ��� ����ϴ� �Լ�) 

	for (size_t i = 0; i < m_vecPlane.size(); ++i)
	{
		if (D3DXPlaneDotCoord(&m_vecPlane[i], &pSphere->vCenter) > pSphere->fRadius)
			return false;
	}

	return true;
}
