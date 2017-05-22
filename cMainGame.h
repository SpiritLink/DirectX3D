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

	LPD3DXMESH		m_pMeshSphere;
	LPD3DXMESH		m_pObjMesh;

	D3DMATERIAL9	m_stMtlSphere1;
	D3DMATERIAL9	m_stMtlSphere2;
	D3DMATERIAL9	m_stMtlNone;
	D3DMATERIAL9	m_stMtlPicked;
	D3DMATERIAL9	m_stMtlPlane;

	ST_SPHERE					m_vSphere;
	std::vector<cGroup*>		m_vecGroup;
	std::vector<ST_PN_VERTEX>	m_vecPlaneVertex;
	std::vector<cMtlTex*>		m_vecObjMtlTex;

	D3DXVECTOR3					m_vPickedPosition;
	LPDIRECT3DTEXTURE9			m_pRawTexture;
	bool						m_bSwitch;

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


};