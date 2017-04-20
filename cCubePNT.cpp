#include "stdafx.h"
#include "cCubePNT.h"


cCubePNT::cCubePNT()
{
}


cCubePNT::~cCubePNT()
{
}

void cCubePNT::Setup()
{
	ST_PNT_VERTEX v;

	D3DXVECTOR3 ptArray[8];
	ptArray[0] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	ptArray[1] = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	ptArray[2] = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	ptArray[3] = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	ptArray[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	ptArray[5] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	ptArray[6] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	ptArray[7] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	v.p = ptArray[0]; m_vecVertex.push_back(v);
	v.p = ptArray[1]; m_vecVertex.push_back(v);
	v.p = ptArray[2]; m_vecVertex.push_back(v);
	v.p = ptArray[0]; m_vecVertex.push_back(v);
	v.p = ptArray[2]; m_vecVertex.push_back(v);
	v.p = ptArray[3]; m_vecVertex.push_back(v);

	v.p = ptArray[4]; m_vecVertex.push_back(v);
	v.p = ptArray[6]; m_vecVertex.push_back(v);
	v.p = ptArray[5]; m_vecVertex.push_back(v);
	v.p = ptArray[4]; m_vecVertex.push_back(v);
	v.p = ptArray[7]; m_vecVertex.push_back(v);
	v.p = ptArray[6]; m_vecVertex.push_back(v);

	v.p = ptArray[4]; m_vecVertex.push_back(v);
	v.p = ptArray[5]; m_vecVertex.push_back(v);
	v.p = ptArray[1]; m_vecVertex.push_back(v);
	v.p = ptArray[4]; m_vecVertex.push_back(v);
	v.p = ptArray[1]; m_vecVertex.push_back(v);
	v.p = ptArray[0]; m_vecVertex.push_back(v);

	v.p = ptArray[3]; m_vecVertex.push_back(v);
	v.p = ptArray[2]; m_vecVertex.push_back(v);
	v.p = ptArray[6]; m_vecVertex.push_back(v);
	v.p = ptArray[3]; m_vecVertex.push_back(v);
	v.p = ptArray[6]; m_vecVertex.push_back(v);
	v.p = ptArray[7]; m_vecVertex.push_back(v);

	v.p = ptArray[1]; m_vecVertex.push_back(v);
	v.p = ptArray[5]; m_vecVertex.push_back(v);
	v.p = ptArray[6]; m_vecVertex.push_back(v);
	v.p = ptArray[1]; m_vecVertex.push_back(v);
	v.p = ptArray[6]; m_vecVertex.push_back(v);
	v.p = ptArray[2]; m_vecVertex.push_back(v);

	v.p = ptArray[4]; m_vecVertex.push_back(v);
	v.p = ptArray[0]; m_vecVertex.push_back(v);
	v.p = ptArray[3]; m_vecVertex.push_back(v);
	v.p = ptArray[4]; m_vecVertex.push_back(v);
	v.p = ptArray[3]; m_vecVertex.push_back(v);
	v.p = ptArray[7]; m_vecVertex.push_back(v);
}

void cCubePNT::Update()
{
}

void cCubePNT::Render()
{
}
