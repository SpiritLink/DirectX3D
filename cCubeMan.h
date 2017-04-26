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
	D3DXVECTOR3					m_vNextPoint;
	int							m_nVecCnt;
	int							m_nType;
public:
	cCubeNode*	m_pRoot;
	D3DMATERIAL9	m_stMaterial;

	virtual void Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType) override;
	virtual void Update() override;
	virtual void Render() override;
	void MoveStraight();
	void MoveCurve();
	void SetMaterial();
};

