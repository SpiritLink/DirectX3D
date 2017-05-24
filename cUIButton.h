#pragma once
#include "cUIObject.h"

class cUIButton;
class iButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};
///할일을 지정해놓고 클릭시 실행시킴
///콜백은 시스템에게 처리해달라고 요청하는것

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

	// >> : 버튼 클릭에 대한 처리
	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);
	// << : 
public:
	virtual void SetTexture(char* szNormal, char* szOver, char* szSelect);
	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};