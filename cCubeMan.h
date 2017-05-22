#pragma once
#include "cCharacter.h"

class cCubeNode;

class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();
protected:
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<ST_PC_VERTEX>*	m_pVertex;
	int							m_nType;
	int							m_nCurrentPoint;
	float						m_fT;
public:
	cCubeNode*	m_pRoot;
	D3DMATERIAL9	m_stMaterial;

	virtual void Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType) override;
	virtual void Setup() override;
	virtual void Update(iMap* pMap) override;
	virtual void Render() override;
	void SetMaterial();
	void MoveStraight();
	void MoveCurve();
};

