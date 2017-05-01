#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cPyramid;
class cCubeMan;
class cGroup;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	//cCubePC*				m_pCubePC;
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;
	cCubeMan*				m_pCubeManStraight;
	cCubeMan*				m_pCubeManCurve;
	std::vector<cGroup*>	m_vecGroup;
public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();
	void Obj_Render();
};