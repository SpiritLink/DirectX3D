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

void cUIImageView::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	RECT rc;
	SetRect(&rc, GetPosition().x, GetPosition().y, GetPosition().x + GetSize().nWidth, GetPosition().y + GetSize().nHeight);
	pSprite->Draw(m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&GetPosition(),
		D3DCOLOR_XRGB(255, 255, 255, 255));
	pSprite->End();

	for each(auto p in m_vecChild)
		p->Render(pSprite);
}
