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
	m_vecVertex.clear();
	ST_PNT_VERTEX ptArray[7];
	ptArray[0].p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	ptArray[1].p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
	ptArray[2].p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);
	ptArray[3].p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
	ptArray[4].p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	ptArray[5].p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	ptArray[6].p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	ptArray[7].p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	ST_PNT_VERTEX v;

	v = ptArray[0];
	m_vecVertex.push_back(v);
	v = ptArray[1]; m_vecVertex.push_back(v);
	v = ptArray[2]; m_vecVertex.push_back(v);
	v = ptArray[0]; m_vecVertex.push_back(v);
	v = ptArray[2]; m_vecVertex.push_back(v);
	v = ptArray[3]; m_vecVertex.push_back(v);

	v = ptArray[4]; m_vecVertex.push_back(v);
	v = ptArray[6]; m_vecVertex.push_back(v);
	v = ptArray[5]; m_vecVertex.push_back(v);
	v = ptArray[4]; m_vecVertex.push_back(v);
	v = ptArray[7]; m_vecVertex.push_back(v);
	v = ptArray[6]; m_vecVertex.push_back(v);

	v = ptArray[4]; m_vecVertex.push_back(v);
	v = ptArray[5]; m_vecVertex.push_back(v);
	v = ptArray[1]; m_vecVertex.push_back(v);
	v = ptArray[4]; m_vecVertex.push_back(v);
	v = ptArray[1]; m_vecVertex.push_back(v);
	v = ptArray[0]; m_vecVertex.push_back(v);

	v = ptArray[3]; m_vecVertex.push_back(v);
	v = ptArray[2]; m_vecVertex.push_back(v);
	v = ptArray[6]; m_vecVertex.push_back(v);
	v = ptArray[3]; m_vecVertex.push_back(v);
	v = ptArray[6]; m_vecVertex.push_back(v);
	v = ptArray[7]; m_vecVertex.push_back(v);

	v = ptArray[1]; m_vecVertex.push_back(v);
	v = ptArray[5]; m_vecVertex.push_back(v);
	v = ptArray[6]; m_vecVertex.push_back(v);
	v = ptArray[1]; m_vecVertex.push_back(v);
	v = ptArray[6]; m_vecVertex.push_back(v);
	v = ptArray[2]; m_vecVertex.push_back(v);

	v = ptArray[4]; m_vecVertex.push_back(v);
	v = ptArray[0]; m_vecVertex.push_back(v);
	v = ptArray[3]; m_vecVertex.push_back(v);
	v = ptArray[4]; m_vecVertex.push_back(v);
	v = ptArray[3]; m_vecVertex.push_back(v);
	v = ptArray[7]; m_vecVertex.push_back(v);
}

void cCubePNT::Update()
{
	// : to do something
}

void cCubePNT::Render()
{
}
