#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
{
}


cUIButton::~cUIButton()
{
	for (int i = 0; i < E_STATE_CNT; ++i)
	{
		SAFE_RELEASE(m_aTexture[i]);
	}
}

void cUIButton::SetTexture(char * szNormal, char * szOver, char * szSelect)
{
	/// Init Normal Texture
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			szNormal,
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
			&m_aTexture[E_NORMAL]);
	}
	/// Init MouseOver Texture
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			szOver,
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
			&m_aTexture[E_MOUSEOVER]);
	}
	/// Init Select Texture
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			szOver,
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
			&m_aTexture[E_SELECTED]);
	}
}

void cUIButton::Update()
{
	for each(auto p in m_vecChild)
		p->Update();
}

void cUIButton::Render(LPD3DXSPRITE pSprite)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	RECT rc;
	SetRect(&rc, GetPosition().x, GetPosition().y, GetPosition().x + GetSize().nWidth, GetPosition().x + GetSize().nHeight);
	switch (m_eButtonState)
	{
	case E_NORMAL:
		pSprite->Draw(m_aTexture[E_NORMAL], &rc, &D3DXVECTOR3(0, 0, 0), &GetPosition(), D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case E_MOUSEOVER:
		pSprite->Draw(m_aTexture[E_MOUSEOVER], &rc, &D3DXVECTOR3(0, 0, 0), &GetPosition(), D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case E_SELECTED:
		pSprite->Draw(m_aTexture[E_SELECTED], &rc, &D3DXVECTOR3(0, 0, 0), &GetPosition(), D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	pSprite->End();
}
