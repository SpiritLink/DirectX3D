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
	: m_pCubePC(NULL)
	, m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pPyramid(NULL)
	, m_pCubeMan(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCubePC);
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

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);//ÇöÀç ºûÀ» »ç¿ëÇÏÁö ¾Ê±â ¶§¹®¿¡ ²¨ÁÜ
}

void cMainGame::Update()
{
	if (m_pCubePC) m_pCubePC->Update();

	if (m_pCamera) m_pCamera->Update();

	if (m_pCubeMan) m_pCubeMan->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();
	if (m_pPyramid) m_pPyramid->Render();
	if (m_pCubePC) m_pCubePC->Render();
	if (m_pCubeMan) m_pCubeMan->Render();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
