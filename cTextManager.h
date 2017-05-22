#pragma once

#define g_pTextManager cTextManager::GetInstance() //

enum POINTER_TYPE
{
	INT_POINTER,
	FLOAT_POINTER
};
struct ST_TEXT
{
	std::string		Text;
	void*			pValue;
	int				nStartX;
	int				nStartY;
	int				nRed;
	int				nBlue;
	int				nGreen;
	POINTER_TYPE	eType;
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
	void AddText(std::string Text, void* pValue, int nStartX, int nStartY, int nRed, int nGreen, int nBlue,POINTER_TYPE type);
	void RemoveText();
	void Render();
	void CursorPosition();
	void FrameCount();
	void Destroy();
};

