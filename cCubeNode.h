#pragma once
#include "cCubePNT.h"
class cCubeNode : public cCubePNT
{
public:
	cCubeNode();

protected:

	float			m_fRotX;
	D3DXVECTOR3		m_vLocalPosition;
	D3DXMATRIXA16	m_matLocalTransMatrix;
	D3DXMATRIXA16	m_matWorldTransMatrix;
	std::vector<cCubeNode*>	m_vecChild;

	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTransMatrix, ParentWorldTransMatrix)
	SYNTHESIZE(float, m_fRotDeltaX, RotateDeltaX)
public:
	

	virtual	~cCubeNode();

	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

	
};

