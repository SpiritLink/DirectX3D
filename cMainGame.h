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

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	cCamera*		m_pCamera;
	cGrid*			m_pGrid;
	cWoman*			m_pWoman;
	cCubeMan*		m_pCubeMan;
	cHeightMap*		m_pMap;

	LPD3DXMESH		m_pObjMesh;

	D3DMATERIAL9	m_stMtlNone;
	D3DMATERIAL9	m_stMtlPicked;
	D3DMATERIAL9	m_stMtlPlane;

	std::vector<cGroup*>		m_vecGroup;
	std::vector<ST_PN_VERTEX>	m_vecPlaneVertex;
	std::vector<cMtlTex*>		m_vecObjMtlTex;

	D3DXVECTOR3					m_vPickedPosition;
	bool						m_bSwitch;

	LPD3DXSPRITE	m_pSprite;
	D3DXIMAGE_INFO	m_stImageInfo;

	LPDIRECT3DTEXTURE9	m_pTexture;

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

	// >> :
	void Setup_UI();
	void UI_Render();
	// << :


};