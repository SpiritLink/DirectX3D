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
class cMtlTex;
class cCharacter;
class cHeightMap;
class cUIObject;
class cSkinnedMesh;
class cFrustum;

#include "cUIButton.h"



class cMainGame : public iButtonDelegate
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	cWoman*			m_pWoman;
	cCubeMan*		m_pCubeMan;
	iMap*			m_pMap;
	cUIObject*		m_pUIRoot;
	cFrustum*		m_pFrustrum;

	LPD3DXMESH		m_pObjMesh;
	LPD3DXMESH		m_pZealot;
	LPD3DXMESH		m_pSphere;
	std::vector<ST_SPHERE>		m_vecStSphere;

	D3DMATERIAL9	m_stMtlNone;
	D3DMATERIAL9	m_stMtlPicked;
	D3DMATERIAL9	m_stMtlPlane;
	std::vector<D3DMATERIAL9>	Mtrls;
	std::vector<IDirect3DTexture9*> Textures;

	std::vector<cGroup*>		m_vecGroup;
	std::vector<ST_PN_VERTEX>	m_vecPlaneVertex;
	std::vector<cMtlTex*>		m_vecObjMtlTex;

	D3DXVECTOR3					m_vPickedPosition;
	bool						m_bSwitch;

	LPD3DXSPRITE	m_pSprite;

	cSkinnedMesh *	m_pSkinnedMesh;

	int nAnimIndex;

	std::vector<int> m_vecChar;


public:
	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Set_Light();
	void Obj_Render();
	void Load_Surface();

	void Setup_MeshObject();
	void Mesh_Render();
	void Setup_HeightMap();
	void Setup_Button();

	void Setup_Frustum();
	void DrawSphere();
	virtual void OnClick(cUIButton* pSender) override;

	void Keyboard();

	std::vector<ST_PC_VERTEX>	m_vecParticleVertex;
	void Setup_Particle();
	void Update_Particle();
	void Render_Particle();
};