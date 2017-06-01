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
	// : 1. ���� ����� ���� ���� 8 ����



	// : 2. �ʱ�ȭ
	m_vecProjVertex = vecVertex;
	m_vecWorldVertex = vecVertex;
	for (int i = 0; i < 6; ++i)
	{
		m_vecPlane.push_back(D3DXPLANE());
	}
}

void cFrustum::Update()
{
	// : 1. viewMatrix, Projection ���ϱ�(getTransForm);
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matProjection;
	D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matView;

	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);	/// �������� ����� ���ɴϴ�.
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);				/// ���� ����� ���ɴϴ�.

	//for (size_t i = 0; i < m_vecProjVertex.size(); ++i)
	//{
	//	D3DXVec3TransformCoord(&m_vecProjVertex[i], &m_vecProjVertex[i], &matView);			/// ���� ���ؽ� ��ȯ
	//	D3DXVec3TransformCoord(&m_vecWorldVertex[i], &m_vecWorldVertex[i], &matWorld);		/// �������� ���ؽ� ��ȯ
	//}
	
	// : 2. D3DXVec3Unproject(1. ��ȯ�� ���� ���ؽ�, �������� ���ؽ�, ����Ʈ (NULL�� ����), �������� ��Ʈ����, ���Ʈ����, �����Ʈ����(NULL�� ����)) ���س���.
	for (size_t i = 0; i < m_vecProjVertex.size(); ++i)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProjection, &matView, NULL);
	}

	// : 3. ���� �����Ѵ�. D3DXPlaneFromPoints() [���� �̿��ؼ� ���� ����] �� ���� 3���� ���������� �� (�׸��� ������ ������ �߿���)
	D3DXPlaneFromPoints(&m_vecPlane[0] , &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5]);
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[7], &m_vecWorldVertex[6], &m_vecWorldVertex[5]);
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[0], &m_vecWorldVertex[3], &m_vecWorldVertex[7]);
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[3], &m_vecWorldVertex[2], &m_vecWorldVertex[7]);
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[1], &m_vecWorldVertex[0], &m_vecWorldVertex[5]);

}

bool cFrustum::IsIn(ST_SPHERE * pSphere)
{
	/// �� �鿡 loop
	// �ȿ� �ִ��� �ۿ� �ִ��� ���� �ִ��� �˻��Ѵ�.
	// D3DXPlaneDotCoord (��, ����) -> ����(�Ÿ�)�� ���� [d��] (��� �������� �Ÿ��� ����ϴ� �Լ�) 

	for (size_t i = 0; i < m_vecPlane.size(); ++i)
	{
		D3DXVECTOR3 center = pSphere->vCenter;
		float Result = D3DXPlaneDotCoord(&m_vecPlane[i], &center);

		if (Result > 0)
		{
			return false;	/// ���� ������ �����Ѵ�.
		}
	}

	return true;
}
