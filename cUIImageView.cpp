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
 *	���Ͽ��� �ؽ��ĸ� �ҷ��� �����մϴ�.
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
	SetRect(&rc, GetPosition().x, GetPosition().y, GetSize().nWidth, GetSize().nHeight);
	pSprite->End();
}
