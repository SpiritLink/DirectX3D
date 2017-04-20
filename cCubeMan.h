#pragma once
#include "cCharacter.h"

class cCubeNode;

class cCubeMan : public cCharacter
{
public:
	cCubeMan();
	~cCubeMan();
public:
	cCubeNode*	m_pRoot;

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;
};

