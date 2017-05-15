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

#include "cMtlTex.h"

cMainGame::cMainGame()
	: //m_pCubePC(NULL),
	m_pGrid(NULL),
	m_pCamera(NULL),
	m_pMap(NULL),
	m_pWoman(NULL),
	m_pFont(NULL),
	m_p3DText(NULL),
	m_pMeshTeapot(NULL),
	m_pMeshSphere(NULL),
	m_pMeshMap(NULL)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pWoman);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pMap);
	SAFE_RELEASE(m_p3DText);
	SAFE_RELEASE(m_pFont);
	for (int i = 0; i < m_vecMap.size(); ++i)
		SAFE_DELETE(m_vecMap[i]);
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pMeshTeapot);
	SAFE_RELEASE(m_pMeshMap);

	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pWoman = new cWoman;
	m_pWoman->Setup();
	Load_Surface();

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pWoman->GetPosition());

	Set_Light();
	Create_Font();

	cObjLoader loadObj;
	//loadObj.Load(m_vecMap, "obj", "Map.obj");
	m_pMeshMap = loadObj.LoadMesh(m_vecSubset, "obj", "Map.obj");
	Setup_MeshObject();
}

void cMainGame::Update()
{
	if (m_pCamera) 
		m_pCamera->Update();
	if (m_pWoman)
		m_pWoman->update();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);
	g_pD3DDevice->BeginScene();


	if (m_pGrid) m_pGrid->Render();
	if (m_pWoman) m_pWoman->Render();

	//Obj_Render();
	//Text_Render();

	//Mesh_Render();
	Mesh_MapRender();
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

void cMainGame::Create_Font()
{
	// >> :
	{
		D3DXFONT_DESC	fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
		fd.Height = 50;
		fd.Width = 40;
		fd.Weight = FW_MEDIUM;
		fd.Italic = false;
		fd.CharSet = DEFAULT_CHARSET;
		fd.OutputPrecision = OUT_DEFAULT_PRECIS;
		fd.PitchAndFamily = FF_DONTCARE;
		AddFontResource("font/NanumBarunGothic.ttf");
		strcpy_s(fd.FaceName, "NanumBarunGothic");

		D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_pFont);
	}

	{
		HDC hdc = CreateCompatibleDC(0);
		LOGFONT lf;
		ZeroMemory(&lf, sizeof(LOGFONT));
		lf.lfHeight = 25;
		lf.lfWidth = 12;
		lf.lfWeight = 500;
		lf.lfItalic = false;
		lf.lfUnderline = false;
		lf.lfStrikeOut = false;
		lf.lfCharSet - DEFAULT_CHARSET;
		strcpy_s(lf.lfFaceName, "굴림체");

		HFONT hFont;
		HFONT hFontOld;
		hFont = CreateFontIndirect(&lf);
		hFontOld = (HFONT)SelectObject(hdc, hFont);
		///숫자가 작을수록 곡선이 부드럽다.
		D3DXCreateText(g_pD3DDevice, hdc, "Direct3D", 0.001f, 0.01f,
			&m_p3DText,
			0, 0);
		SelectObject(hdc, hFontOld);
		DeleteObject(hFont);
		DeleteDC(hdc);
	}
	// << :
}

void cMainGame::Text_Render()
{
	{
		std::string sText = std::to_string(g_nFrameCount);
		RECT rc;
		SetRect(&rc, 0, 0, 1, 0);
		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(0, 255, 0));
	}

	{
		D3DXMATRIXA16 matWorld, matS, matR, matT;
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);

		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 100.0f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0F);
		D3DXMatrixTranslation(&matT, -2.0f, 2.0f, 0.0f);
		matWorld = matS * matR * matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_p3DText->DrawSubset(0);
	}
}

void cMainGame::Setup_MeshObject()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7F, 0.7F, 1.0F);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7F, 0.7F, 1.0F);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7F, 0.7F, 1.0F);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.0f, 0.7F, 0.7F, 1.0F);
	m_stMtlSphere.Specular = D3DXCOLOR(0.0f, 0.7F, 0.7F, 1.0F);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.0f, 0.7F, 0.7F, 1.0F);

}

void cMainGame::Mesh_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld,
			0, 0, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot);
		m_pMeshTeapot->DrawSubset(0);
	}

	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld,
			0, 0, 0);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);
	}
}

void cMainGame::Mesh_MapRender()
{
	for (int i = 0; i < m_vecSubset.size(); ++i)
	{
		g_pD3DDevice->SetMaterial(&m_vecSubset[i]->GetMaterial());
		g_pD3DDevice->SetTexture(0,m_vecSubset[i]->GetTexture());
		m_pMeshMap->DrawSubset(i);
	}
}
