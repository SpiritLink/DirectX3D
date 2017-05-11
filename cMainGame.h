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
	cCubeMan*				m_pCubeMan;
	cCubeMan*				m_pCubeManCurve;
	cWoman*					m_pWoman;
	std::vector<cGroup*>	m_vecGroup;
	std::vector<cGroup*>	m_vecMap;

	iMap* m_pMap; // << :
	
	cFrame*					m_pRootFrame;
	cFrame*					m_pRootStand;
public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();
	void Obj_Render();
	void Load_Surface();
};