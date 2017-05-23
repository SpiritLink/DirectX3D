#pragma once
#include "cObject.h"
class cUIObject :
	public cObject
{
public:
	cUIObject();
	virtual ~cUIObject();
protected:
	std::vector<cUIObject*> m_vecChild;
	D3DXMATRIXA16			m_matWorld;
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(cUIObject*, m_pParent, Parent);
	SYNTHESIZE(ST_SIZEN, m_stSize, Size);

	// >> : tag

	// << :
	bool m_isHidden;
public:
	virtual void SetPosition(float x, float y, float z = 0);
	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();

	// >> : tag
	// << :
};

