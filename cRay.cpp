#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	:m_vOriginal(0,0,0),
	m_vDirection(0,0,0),
	m_eRaySpace(E_NONE)
{
}


cRay::~cRay()
{
}

cRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9 ViewPort;
	g_pD3DDevice->GetViewport(&ViewPort);

	D3DXMATRIXA16 MatProjection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &MatProjection);

	cRay r;
	r.m_vDirection.x = ((2.0f * nScreenX) / ViewPort.Width - 1.0f) / MatProjection._11;
	r.m_vDirection.y = ((-2.0f * nScreenY) / ViewPort.Height + 1.0f) / MatProjection._22;	///스크린이 출력시 뒤집어지기 때문
	r.m_vDirection.z = 1.0f;
	r.m_eRaySpace = E_VIEW;
	return r;
}

cRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay r = cRay::RayAtViewSpace(nScreenX, nScreenY);

	D3DXMATRIXA16 matView, matInvView;
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, 0, &matView);

	D3DXVec3TransformCoord(&r.m_vOriginal, &r.m_vOriginal, &matInvView);
	D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &matInvView);
	D3DXVec3Normalize(&r.m_vDirection, &r.m_vDirection);

	r.m_eRaySpace = E_WORLD;
	return r;
}

bool cRay::IntersectTri(IN D3DXVECTOR3 & v0, IN D3DXVECTOR3 & v1, IN D3DXVECTOR3 & v2, OUT D3DXVECTOR3 & vPickedPosition)
{
	float u, v, t;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOriginal, &m_vDirection, &u, &v, &t);
	vPickedPosition = m_vOriginal + (t * m_vDirection);

	return b;
}

bool cRay::IsPicked(ST_SPHERE * pSphere)
{
	cRay r = (*this);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pSphere->vCenter.x;
	matInvWorld._42 = -pSphere->vCenter.y;
	matInvWorld._43 = -pSphere->vCenter.z;

	D3DXVec3TransformCoord(&r.m_vOriginal, &r.m_vOriginal, &matInvWorld);
	D3DXVec3TransformNormal(&r.m_vDirection, &r.m_vDirection, &matInvWorld);

	float vv = D3DXVec3Dot(&r.m_vDirection, &r.m_vDirection);
	float qv = D3DXVec3Dot(&r.m_vOriginal, &r.m_vDirection);
	float qq = D3DXVec3Dot(&r.m_vOriginal, &r.m_vOriginal);
	float rr = pSphere->fRadius * pSphere->fRadius;

	return qv*qv - vv * (qq - rr) >= 0;

}
