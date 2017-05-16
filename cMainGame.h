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
	iMap* m_pMap;
	LPD3DXFONT				m_pFont;
	ID3DXMesh*				m_p3DText;

	LPD3DXMESH				m_pMeshTeapot;
	LPD3DXMESH				m_pMeshSphere;
	D3DMATERIAL9			m_stMtlTeapot;
	D3DMATERIAL9			m_stMtlSphere;

	LPD3DXMESH				m_pObjMesh;
	std::vector<cMtlTex*>	m_vecObjMtlTex;
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
	void Mesh_Render();
};