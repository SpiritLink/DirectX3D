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

void cWoman::Render()
{
	cGroup::Render();
	for (int i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->Render();
	}
}
