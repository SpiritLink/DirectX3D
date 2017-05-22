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
	iMap*					m_pMap;
	LPD3DXFONT				m_pFont;

	LPD3DXMESH				m_pMeshSphere;
	D3DMATERIAL9			m_stMtlSphere1;
	D3DMATERIAL9			m_stMtlSphere2;

	LPD3DXMESH				m_pObjMesh;
	std::vector<cMtlTex*>	m_vecObjMtlTex;

	ST_SPHERE				m_vSphere;
	bool					m_bSwitch;

	std::vector<ST_SPHERE>		m_vecSphere;
	D3DMATERIAL9				m_stMtlNone;
	D3DMATERIAL9				m_stMtlPicked;
	D3DMATERIAL9				m_stMtlPlane;
	std::vector<ST_PN_VERTEX>	m_vecPlaneVertex;
	D3DXVECTOR3					m_vPickedPosition;

	std::vector<ST_PNT_VERTEX>	m_vecRawMap;
	LPD3DXMESH				m_pRawMap;
	LPDIRECT3DTEXTURE9		m_pRawTexture;

	cCharacter*				m_pCubeMan;
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

	void Setup_MeshObject();
	std::vector<ST_PNT_VERTEX> Setup_RawMap(IN char * szFolder, IN char * szFile);
	void Mesh_Render();
	void RawMap_Render();
	bool GridCollision(IN cGrid* m_pGrid, IN D3DXVECTOR3* vRayPosition, IN D3DXVECTOR3* vRayDirection, OUT D3DXVECTOR3* Destination);
	void Setup_PickingObj();
	void PickingObj_Render();
	void RawMapCollision(cWoman* Woman, std::vector<ST_PNT_VERTEX> vecMap);

	void Setup_HeightMap();


};