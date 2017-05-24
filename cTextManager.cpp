#include "stdafx.h"
#include "cTextManager.h"


cTextManager::cTextManager()
	:m_pFont(NULL)
{
}


cTextManager::~cTextManager()
{
	SAFE_RELEASE(m_pFont);
}

/*-----------------------------------------
 * Key에 해당하는 Font를 반환합니다.
 * 없다면 파일로부터 읽은뒤 Map에 저장합니다.
 */
LPD3DXFONT cTextManager::GetFont(char * KeyName)
{
	return GetFont(std::string(KeyName));
}

LPD3DXFONT cTextManager::GetFont(std::string keyName)
{
	///해당 폰트가 없다면 폰트를 생성합니다.
	if (m_mapFont.find(keyName) == m_mapFont.end())
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 30;
		fd.Width = 25;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		std::string name = keyName;
		std::string szFullPath = std::string("font/") + name + std::string(".ttf");
		AddFontResource(szFullPath.c_str());
		strcpy_s(fd.FaceName, name.c_str());
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[keyName]);
	}
	/// 있다면 반환함
	if (m_mapFont.find(keyName) != m_mapFont.end())
		return m_mapFont[keyName];

	/// 없다면 NULL을 반환합니다. (파일이 없거나 잘못된 키를 입력)
	return NULL;
}

void cTextManager::TextRender(std::string Text, void * pValue, int nStartX, int nStartY, POINTER_TYPE type)
{
	TextRender(Text, pValue, nStartX, nStartY, 0, 0, 0, type);	
}
void cTextManager::TextRender(std::string Text, void * pValue, int nStartX, int nStartY, int nR, int nG, int nB, POINTER_TYPE type)
{
	int x = nStartX;
	int y = nStartY;
	std::string sText = Text;

	switch (type)
	{
	case INT_POINTER:
		sText += std::to_string(*(int *)pValue);
		break;
	case FLOAT_POINTER:
		sText += std::to_string(*(float *)pValue);
		break;
	}
	RECT rc;
	SetRect(&rc, x, y, x + 1, y);

	int R, G, B;
	R = nR;
	G = nG;
	B = nB;

	m_mapFont["NanumBarunGothic"]->DrawTextA(NULL,
		sText.c_str(),
		sText.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(R, G, B));
}