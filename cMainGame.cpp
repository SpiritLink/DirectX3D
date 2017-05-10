#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"		/// << :

#include "cCubePC.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cCubeMan.h"

#include "cGroup.h"
#include "cObjLoader.h"
#include "cObject.h"
#include "cObjMap.h"

#include "cAseLoader.h"
#include "cWoman.h"
#include "cFrame.h"

cMainGame::cMainGame()
	: //m_pCubePC(NULL),
	m_pGrid(NULL),
	m_pCamera(NULL),
	m_pCubeMan(NULL),
	m_pCubeManCurve(NULL),
	m_pMap(NULL),
	m_pWoman(NULL),
	m_pRootFrame(NULL)
{
}


cMainGame::~cMainGame()
{
	//SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pCubeManCurve)
	SAFE_DELETE(m_pMap);
	g_pDeviceManager->Destroy();
	m_pRootFrame->Destroy();
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	//cObjLoader loadObj;
	//loadObj.Load(m_vecGroup, "obj", "Map.obj");
	//loadObj.Load(m_vecMap, "obj", "Map_surface.obj");

	cAseLoader loadAse;
	m_pRootFrame = loadAse.Load("woman/woman_01_all.ASE");
	Load_Surface();

	//m_pCubeMan = new cCubeMan;
	//m_pCubeMan->Setup(m_pGrid->getVertex(), 1);

	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	Set_Light();
}

void cMainGame::Update()
{
	//if (m_pCubePC) m_pCubePC->Update();

	if (m_pCamera) m_pCamera->Update();
	if (m_pCubeMan) m_pCubeMan->Update(m_pMap);
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();

	//Obj_Render();

	//if (m_pCubeMan) m_pCubeMan->Render();
	//if (m_pWoman) m_pWoman->Render();

	if (m_pRootFrame) 
		m_pRootFrame->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight3;
	ZeroMemory(&stLight3, sizeof(D3DLIGHT9));
	stLight3.Type = D3DLIGHT_DIRECTIONAL;
	stLight3.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight3.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight3.Specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);

	//빛의 방향 설정
	D3DXVECTOR3 vDir3(1.0f, -3.0f, 1.0f);
	D3DXVec3Normalize(&vDir3, &vDir3);
	stLight3.Direction = vDir3;

	g_pD3DDevice->SetLight(2, &stLight3);
	g_pD3DDevice->LightEnable(2, true);

}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for each(auto p in m_vecMap)
	{
		p->Render();
	}
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;

	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}
