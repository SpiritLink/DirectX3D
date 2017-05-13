#pragma once
#include "stdafx.h"
#include "cObject.h"
#include "cMtlTex.h"

class cGroup : public cObject
{
public:
	cGroup();
	~cGroup();
protected:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	SYNTHESIZE(int, m_nNumTri, NumTri);
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
public:
	void Render();
	void BuildVertexBuffer();
};