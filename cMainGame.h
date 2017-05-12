#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cPyramid;
class cCubeMan;
class cGroup;
class cWoman;
class iMap;
class cFrame;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;
	cWoman*					m_pWoman;
	std::vector<cGroup*>	m_vecGroup;
	std::vector<cGroup*>	m_vecMap;
	iMap* m_pMap; // << :
	LPD3DXFONT				m_pFont;
public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();
	void Obj_Render();
	void Load_Surface();

	void Create_Font();
	void Text_Render();
};