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
	m_pPyramid(NULL),
	m_pCubeMan(NULL)
{
}


cMainGame::~cMainGame()
{
	//SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPyramid);
	SAFE_DELETE(m_pCubeMan);
	g_pDeviceManager->Destroy();	//¼Ò¸êÀÚ ¿ªÈ°À» ÇÏ°Ô²û ¸¸µë
}

void cMainGame::Setup()
{
	//m_pCubePC = new cCubePC;
	//m_pCubePC->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pPyramid = new cPyramid;
	m_pPyramid->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);//ÇöÀç ºûÀ» »ç¿ëÇÏÁö ¾Ê±â ¶§¹®¿¡ ²¨ÁÜ
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	Set_Light();
}

void cMainGame::Update()
{
	//if (m_pCubePC) m_pCubePC->Update();

	if (m_pCamera) m_pCamera->Update();

	if (m_pCubeMan) m_pCubeMan->Update();

	if (GetKeyState('1') & 0x8000)			//Æ÷ÀÎÆ®
	{
		g_pD3DDevice->LightEnable(0, true);
		g_pD3DDevice->LightEnable(1, false);
		g_pD3DDevice->LightEnable(2, false);
	}
	if (GetKeyState('2') & 0x8000)			//½ºÆÌ
	{
		g_pD3DDevice->LightEnable(0, false);
		g_pD3DDevice->LightEnable(1, true);
		g_pD3DDevice->LightEnable(2, false);
	}
	if (GetKeyState('3') & 0x8000)			//µð·º¼Å³Î
	{
		g_pD3DDevice->LightEnable(0, false);
		g_pD3DDevice->LightEnable(1, false);
		g_pD3DDevice->LightEnable(2, true);
	}
	if (GetKeyState('4') & 0x8000)			//ÀüºÎÅ´
	{
		g_pD3DDevice->LightEnable(0, true);
		g_pD3DDevice->LightEnable(1, true);
		g_pD3DDevice->LightEnable(2, true);
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();
	if (m_pPyramid) m_pPyramid->Render();
	//if (m_pCubePC) m_pCubePC->Render();
	if (m_pCubeMan) m_pCubeMan->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight1;
	ZeroMemory(&stLight1, sizeof(D3DLIGHT9));
	stLight1.Type = D3DLIGHT_POINT;
	stLight1.Ambient = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	stLight1.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	stLight1.Specular = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	stLight1.Position = D3DXVECTOR3(-2.0f, -2.0f, 4.0f);
	stLight1.Range = 6.0f;

	g_pD3DDevice->SetLight(0, &stLight1);
	g_pD3DDevice->LightEnable(0, true);
	//ºûÀÇ °¨¼â ¼³Á¤
	stLight1.Attenuation0 = 0.0f;
	stLight1.Attenuation1 = 0.0f;
	stLight1.Attenuation2 = 0.0f;

	D3DLIGHT9 stLight2;
	ZeroMemory(&stLight2, sizeof(D3DLIGHT9));
	stLight2.Type = D3DLIGHT_SPOT;
	stLight2.Ambient = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	stLight2.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	stLight2.Specular = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	stLight2.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	stLight2.Falloff = 1.0f;
	stLight2.Range = 10.0f;
	stLight2.Theta = D3DX_PI / 18.0f;
	stLight2.Phi = D3DX_PI / 4.5f;

	//ºûÀÇ ¹æÇâ ¼³Á¤
	D3DXVECTOR3 vDir(1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight2.Direction = vDir;

	//ºûÀÇ °¨¼â ¼³Á¤
	stLight2.Attenuation0 = 0.0f;
	stLight2.Attenuation1 = 0.0f;
	stLight2.Attenuation2 = 0.0f;

	g_pD3DDevice->SetLight(1, &stLight2);
	g_pD3DDevice->LightEnable(1, false);

	D3DLIGHT9 stLight3;
	ZeroMemory(&stLight3, sizeof(D3DLIGHT9));
	stLight3.Type = D3DLIGHT_DIRECTIONAL;
	stLight3.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight3.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight3.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	//ºûÀÇ ¹æÇâ ¼³Á¤
	D3DXVECTOR3 vDir3(1.0f, 3.0f, 1.0f);
	D3DXVec3Normalize(&vDir3, &vDir3);
	stLight3.Direction = vDir3;

	g_pD3DDevice->SetLight(2, &stLight3);
	g_pD3DDevice->LightEnable(2, false);

}
