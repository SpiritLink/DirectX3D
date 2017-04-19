#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame()
// >> : 
	: m_pD3D(NULL)
	, m_pD3DDevice(NULL)
	// << : 
{
}


cMainGame::~cMainGame()
{
	// >> : 
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DDevice);
	// << : 
}

// >> : 
void cMainGame::Setup()
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9	stCaps;
	int			nVertexProcessing;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);
	//stCaps°¡ OutPutÀÓ
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE;
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice);
}

void cMainGame::Update()
{

}

void cMainGame::Render()
{
	m_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	m_pD3DDevice->BeginScene();

	//  :Draw

	m_pD3DDevice->EndScene();

	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
// << : 