#pragma once

#define g_pTextManager cTextManager::GetInstance() //

struct ST_TEXT
{
	std::string Text;
	int*		pValue;
	int			nStartX;
	int			nStartY;
	int			nRed;
	int			nBlue;
	int			nGreen;
};
class cTextManager
{
//public:
//	cTextManager();
//	~cTextManager();
private:
	SINGLETONE(cTextManager);
	std::vector<ST_TEXT>	m_vecText;
	LPD3DXFONT				m_pFont;

public:
	void Create_Font();
	void AddText(std::string Text, int* pValue, int nStartX, int nStartY, int nRed, int nGreen, int nBlue);
	void RemoveText();
	void Render();
	void CursorPosition();
	void FrameCount();
	void Destroy();
};

