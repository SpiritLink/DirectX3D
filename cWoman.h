#pragma once
#include "cGroup.h"

class cWoman : public cGroup
{
protected:
	D3DXMATRIXA16	m_matLocalTransMatrix;
	D3DXMATRIXA16	m_matWorldTransMatrix;
	D3DXMATRIXA16	m_matR;
	std::vector<cWoman*>	m_vecChild;

	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTransMatrix, ParentWorldTransMatrix)
	SYNTHESIZE(D3DXVECTOR3, m_vLocalPosition, LocalPosition)
public:
	cWoman();
	~cWoman();
	void addChild(cWoman* pWoman);
	void SetWorldMatrix(D3DXMATRIXA16* matWorld) { m_matWorldTransMatrix = *matWorld; };
	void update();
	void Render();
};

