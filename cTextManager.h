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
	std::map<std::string, LPD3DXFONT> m_mapFont;
	LPD3DXFONT				m_pFont;

public:
	LPD3DXFONT GetFont(char* KeyName);
	LPD3DXFONT GetFont(std::string keyName);
	void TextRender(std::string Text, void* pValue, int nStartX, int nStartY, POINTER_TYPE type);
	void TextRender(std::string Text, void* pValue, int nStartX, int nStartY, int nR, int nG, int nB, POINTER_TYPE type);
};

