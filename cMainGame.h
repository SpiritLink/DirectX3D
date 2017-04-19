#pragma once
class cCubePC;
class cCamera;
class cGrid;
class cPyramid;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCubePC*	m_pCubePC;
	cCamera*	m_pCamera;
	cGrid*		m_pGrid;
	cPyramid*	m_pPyramid;
public:
	void Setup();
	void Update();
	void Render();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};