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
		case 0:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 31, 20, 39, 31); break;
		case 6:		cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 17, 20, 30, 31); break;
		case 12:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 31, 20, 39, 31); break;
		case 18:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 0, 20, 15, 31); break;
		case 24:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 24, 8, 31, 15); break;
		case 30:	cCubeNode::SetCubeTexturePixel(&m_vecVertex, i, 24, 8, 31, 15); break;
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
