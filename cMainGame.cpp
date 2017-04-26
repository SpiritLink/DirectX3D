#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"		/// << :

// >> :
#include "cCubePC.h"
#include "cGrid.h"
#include "cCamera.h"
#include "cPyramid.h"
#include "cCubeMan.h"

// << :
cMainGame::cMainGame()
	: //m_pCubePC(NULL),
	m_pGrid(NULL),
	m_pCamera(NULL),
	m_pCubeManStraight(NULL),
	m_pCubeManCurve(NULL)
{
}


cMainGame::~cMainGame()
{
	//SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCubeManStraight);
	SAFE_DELETE(m_pCubeManCurve);
	g_pDeviceManager->Destroy();	//¼Ò¸êÀÚ ¿ªÈ°À» ÇÏ°Ô²û ¸¸µë
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pCubeManStraight = new cCubeMan;
	m_pCubeManStraight->Setup(m_pGrid->getVertex(),1);

	m_pCubeManCurve = new cCubeMan;
	m_pCubeManCurve->Setup(m_pGrid->getVertex(), 2);

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeManStraight->GetPosition());

	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);//ÇöÀç ºûÀ» »ç¿ëÇÏÁö ¾Ê±â ¶§¹®¿¡ ²¨ÁÜ
	Set_Light();
}

void cMainGame::Update()
{
	//if (m_pCubePC) m_pCubePC->Update();

	if (m_pCamera) m_pCamera->Update();
	if (m_pCubeManStraight) m_pCubeManStraight->Update();
	if (m_pCubeManCurve) m_pCubeManCurve->Update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();
	//if (m_pCubePC) m_pCubePC->Render();
	//if (m_pCubeManStraight) m_pCubeManStraight->Render();
	if (m_pCubeManCurve) m_pCubeManCurve->Render();

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

	//ºûÀÇ ¹æÇâ ¼³Á¤
	D3DXVECTOR3 vDir3(1.0f, -3.0f, 1.0f);
	D3DXVec3Normalize(&vDir3, &vDir3);
	stLight3.Direction = vDir3;

	g_pD3DDevice->SetLight(2, &stLight3);
	g_pD3DDevice->LightEnable(2, true);

}
