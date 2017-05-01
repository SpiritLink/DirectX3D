#pragma once
#include "cCharacter.h"

class cCubeNode;
class cGroup;

class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();
protected:
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::vector<ST_PC_VERTEX>*	m_pVertex;
	std::vector<cGroup*>* m_pVecGroup;
	float m_pU;
	float m_pV;
	float m_pDist;
public:
	cCubeNode*	m_pRoot;
	D3DMATERIAL9	m_stMaterial;

	virtual void Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType) override;
	virtual void Update() override;
	virtual void Render() override;
	void SetMaterial();
	void SetGroup(std::vector<cGroup*>* vecGroup) { m_pVecGroup = vecGroup; }
	void CollisionCheck();
};

