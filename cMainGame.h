#pragma once
class cCamera;
class cGrid;
class cCubePc;

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	//LPDIRECT3D9				m_pD3D;
	//LPDIRECT3DDEVICE9		m_pD3DDevice;

	cCubePc*		m_pCubePC;
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
public:
	void Setup();
	void Update();
	void Render();
};

