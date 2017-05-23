#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_pParent(NULL),
	m_vPosition(0, 0, 0)
{
	m_stSize.nWidth = 0;
	m_stSize.nHeight = 0;
}


cUIObject::~cUIObject()
{
}

void cUIObject::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
}

void cUIObject::AddChild(cUIObject * pChild)
{
	pChild->SetParent(this);
	m_vecChild.push_back(pChild);
}

void cUIObject::Update()
{
	///부모의 좌표를 기준으로 자신의 좌표를 재설정한다.
	for each(auto p in m_vecChild)
		p->Update();
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->End();

	for each(auto p in m_vecChild)
		p->Render(pSprite);
}

void cUIObject::Destroy()
{
	for each(auto p in m_vecChild)
		p->Destroy();

	delete this;
}
