#include "stdafx.h"
#include "cGroup.h"


cGroup::cGroup()
	: m_pMtlTex(NULL),
	m_nNumTri(0),
	m_pVB(NULL)
{
}

cGroup::~cGroup()
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pVB);
}

void cGroup::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());
	}

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PNT_VERTEX));
}

void cGroup::BuildVertexBuffer()
{
	m_nNumTri = m_vecVertex.size() / 3;
	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	ST_PNT_VERTEX* pv = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pv, 0);
	memcpy_s(pv, m_vecVertex.size() * sizeof(ST_PNT_VERTEX),&m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();
}
