#include "stdafx.h"
#include "cBody.h"


cBody::cBody()
{
}


cBody::~cBody()
{
}

void cBody::Setup()
{
	cCubeNode::Setup();

	for (size_t i = 0; i < m_vecVertex.size(); i += 6)
	{
		switch (i)
		{
		case 0:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 16, 16, 32, 32); break;	//전면
		case 6:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 0, 16, 16, 32); break;	//후면
		case 12:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 0, 8, 8, 16); break;	//좌면
		case 18:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 16, 8, 24, 16); break;	//우면
		case 24:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 8, 0, 16, 8); break;	//상단
		case 30:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 16, 0, 24, 8); break;	//하단
		}
	}

	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p,
			&m_vecVertex[i].p,
			&mat);
	}
}
