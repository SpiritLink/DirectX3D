#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
{
}


cUIImageView::~cUIImageView()
{
	SAFE_RELEASE(m_pTexture);
}
/*------------------------------------
 *	파일에서 텍스쳐를 불러와 저장합니다.
 *------------------------------------
 */
void cUIImageView::SetTexture(char * szFullPath)
{
	D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		szFullPath,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		NULL,
		NULL,
		&m_pTexture);
}

void cUIImageView::Update()
{
	RECT rc;
	int nX = GetPosition().x;
	int nY = GetPosition().y;
	if (GetParent())
	{
		nX += GetParent()->GetPosition().x;
		nY += GetParent()->GetPosition().y;
	}
	SetRect(&rc, nX, nY, nX + GetSize().nWidth, nY + GetSize().nHeight);

	int deltaX = g_ptMouse.x - g_ptPrevMouse.x;
	int deltaY = g_ptMouse.y - g_ptPrevMouse.y;
	if (GetAsyncKeyState(VK_LBUTTON) && PtInRect(&rc, g_ptMouse))
	{
		SetPosition(GetPosition().x + deltaX , GetPosition().y + deltaY, GetPosition().z);
		g_ptPrevMouse = g_ptMouse;
	}
	for each(auto p in m_vecChild)
		p->Update();
}

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	D3DXVECTOR3 position = GetPosition();
	if (GetParent())
		position = GetParent()->GetPosition() + GetPosition();

	RECT rc;
	SetRect(&rc, 0, 0, GetSize().nWidth, GetSize().nHeight);
	pSprite->Draw(m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&position,
		D3DCOLOR_XRGB(255, 255, 255, 255));
	pSprite->End();

	for each(auto p in m_vecChild)
		p->Render(pSprite);
}
