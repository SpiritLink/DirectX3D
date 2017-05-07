#include "stdafx.h"
#include "cWoman.h"


cWoman::cWoman()
	: m_vLocalPosition(0,0,0),
	m_pParentWorldTransMatrix(NULL)
{
	D3DXMatrixIdentity(&m_matLocalTransMatrix);
	D3DXMatrixIdentity(&m_matWorldTransMatrix);
	D3DXMatrixIdentity(&m_matR);
}


cWoman::~cWoman()
{
}

void cWoman::addChild(cWoman * pWoman)
{
	pWoman->SetParentWorldTransMatrix(&m_matWorldTransMatrix);
	m_vecChild.push_back(pWoman);
}

void cWoman::update()
{
	D3DXMatrixTranslation(&m_matLocalTransMatrix,
		m_vLocalPosition.x,
		m_vLocalPosition.y,
		m_vLocalPosition.z);

	m_matLocalTransMatrix = m_matR * m_matLocalTransMatrix;

	//if (m_pParentWorldTransMatrix)
	//	m_matLocalTransMatrix *= *m_pParentWorldTransMatrix;
	for each(auto p in m_vecChild)
	{
		p->update();
	}
}

void cWoman::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matLocalTransMatrix);
	cGroup::Render();
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Render();
	}
}
