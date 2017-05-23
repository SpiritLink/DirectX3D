#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
{
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
	///�θ��� ��ǥ�� �������� �ڽ��� ��ǥ�� �缳���Ѵ�.
	for each(auto p in m_vecChild)
		p->Update();
}

void cUIObject::Render(LPD3DXSPRITE pSprite)
{
}

void cUIObject::Destroy()
{
	for each(auto p in m_vecChild)
		p->Destroy();

	delete this;
}
