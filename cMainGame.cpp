#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"		/// << :

cMainGame::cMainGame()
//: m_pD3D(NULL), m_pD3DDevice(NULL)
{
}


cMainGame::~cMainGame()
{
	//SAFE_RELEASE(m_pD3D);
	//SAFE_RELEASE(m_pD3DDevice);
	g_pDeviceManager->Destroy();	//¼Ò¸êÀÚ ¿ªÈ°À» ÇÏ°Ô²û ¸¸µë
}

void cMainGame::Setup()
{
}

void cMainGame::Update()
{
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	g_pD3DDevice->BeginScene();

	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
