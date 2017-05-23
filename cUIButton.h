#pragma once
#include "cUIObject.h"
class cUIButton :
	public cUIObject
{
public:
	cUIButton();
	virtual ~cUIButton();
protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_STATE_CNT
	};
	eButtonState	m_eButtonState;
	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_CNT];

	// >> : ��ư Ŭ���� ���� ó��
	// << : 
public:
	virtual void SetTexture(char* szNormal, char* szOver, char* szSelect);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};