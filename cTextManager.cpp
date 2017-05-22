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


void cTextManager::Create_Font()
{
		/// ³ª´® ¹Ù¸¥ °íµñÃ¼ µî·Ï
		D3DXFONT_DESC	fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 50;
		fd.Width = 40;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		AddFontResource("font/NanumBarunGothic.ttf");
		strcpy_s(fd.FaceName, "NanumBarunGothic");
		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);

		/// ±¼¸²Ã¼ µî·Ï
		HDC hdc = CreateCompatibleDC(0);
		LOGFONT lf;
		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = 25;
		lf.lfWidth = 12;
		lf.lfWeight = 500;
		lf.lfItalic = false;
		lf.lfUnderline = false;
		lf.lfStrikeOut = false;
		lf.lfCharSet = DEFAULT_CHARSET;
		strcpy_s(lf.lfFaceName, "±¼¸²Ã¼");
}

void cTextManager::AddText(std::string Text, void* pValue, int nStartX, int nStartY, int nRed, int nGreen, int nBlue)
{
	ST_TEXT stText;
	stText.Text = Text;
	stText.pValue = pValue;
	stText.nStartX = nStartX;
	stText.nStartY = nStartY;
	stText.nRed = nRed;
	stText.nGreen = nGreen;
	stText.nBlue = nBlue;

	m_vecText.push_back(stText);
}

void cTextManager::RemoveText()
{
	m_vecText.clear();
}

void cTextManager::Render()
{
	FrameCount();
	CursorPosition();
	for (size_t i = 0; i < m_vecText.size(); ++i)
	{
		std::string sText = m_vecText[i].Text + std::string(":") + std::to_string(*(float *)m_vecText[i].pValue);
		RECT rc;
		int x = m_vecText[i].nStartX;
		int y = m_vecText[i].nStartY;
		SetRect(&rc, x, y, x + 1, y);

		int R, G, B;
		R = m_vecText[i].nRed;
		G = m_vecText[i].nGreen;
		B = m_vecText[i].nBlue;

		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(R, G, B));
	}
}
void cTextManager::CursorPosition()
{
	std::string sText = std::string("X:") + std::to_string(g_ptMouse.x);
	RECT rc;
	SetRect(&rc, 0, 40, 1, 40);

	if (m_pFont)
		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));

	sText = std::string("Y:") + std::to_string(g_ptMouse.y);
	SetRect(&rc, 0, 80, 1, 80);

	if(m_pFont)
		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
}

void cTextManager::FrameCount()
{
	std::string sText = std::string("FPS:") + std::to_string(g_nFrameCount);
	RECT rc;
	SetRect(&rc, 0, 0, 1, 0);
	if (m_pFont)
		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(0, 255, 0));
}

void cTextManager::Destroy()
{
	SAFE_RELEASE(m_pFont);
	m_vecText.clear();
}
