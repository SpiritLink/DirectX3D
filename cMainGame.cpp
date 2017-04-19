#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"				//<<::


//>>::
#include "cCubePc.h"
#include "cGrid.h"
#include "cCamera.h"

//<<::
cMainGame::cMainGame()
	:m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
{
}


cMainGame::~cMainGame()
{
	//SAFE_RELEASE(m_pD3D);
	//SAFE_RELEASE(m_pD3DDevice);
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);


	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pCubePC = new cCubePc;
	m_pCubePC->Setup();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubePC->GetPosition());


	//cGrid;
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);



}

void cMainGame::Update()
{
	if (m_pCubePC)m_pCubePC->Update();
	if (m_pCamera)m_pCamera->Update();

}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pD3DDevice->BeginScene();

	if (m_pGrid) m_pGrid->Render();
	if (m_pCubePC) m_pCubePC->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
