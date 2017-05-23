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

#include "cRay.h"
#include "cRawLoader.h"

#include "cHeightMap.h"
#define SPHERERADIUS 0.5f
#define RAWSIZE 257
#define TILESIZE 256


cMainGame::cMainGame()
	: m_pGrid(NULL),
	m_pCamera(NULL),
	m_pMap(NULL),
	m_pWoman(NULL),
	m_pObjMesh(NULL),
	m_bSwitch(true),
	m_pCubeMan(NULL),
	// >> :
	m_pSprite(NULL),
	m_pTexture(NULL)
	// << :
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pWoman);
	SAFE_RELEASE(m_pObjMesh);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pCubeMan);
	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		SAFE_RELEASE(m_vecObjMtlTex[i]);
	// >> :
	SAFE_RELEASE(m_pSprite);
	SAFE_RELEASE(m_pTexture);
	// << :
	g_pTextManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	g_pTextManager->Create_Font();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pWoman = new cWoman;
	m_pWoman->Setup();
	Load_Surface();
	{
		cCubeMan* pCubeMan = new cCubeMan;
		pCubeMan->Setup();
		m_pCubeMan = pCubeMan;
		Setup_HeightMap();
	}

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	Set_Light();
	Setup_MeshObject();
	Setup_UI();
}

void cMainGame::Update()
{
	if (m_pCamera) 
		m_pCamera->Update();
	if (m_pWoman)
		m_pWoman->update();
	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);
	g_pD3DDevice->BeginScene();


	//if (m_pGrid) m_pGrid->Render();
	if (m_pMap)
		m_pMap->Render();
	//if (m_pWoman) 
	//	m_pWoman->Render();
	if (m_pCubeMan) 
		m_pCubeMan->Render();
	//Obj_Render();
	Mesh_Render();
	//PickingObj_Render();
	UI_Render();	///UI가 최하단에 위치해야됨

	g_pTextManager->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	}
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
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);
	matWorld = matS * matR;

	//m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

void cMainGame::Setup_MeshObject()
{
}

void cMainGame::Mesh_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;

}

void cMainGame::Setup_HeightMap()
{
	cHeightMap *pMap = new cHeightMap;
	pMap->Setup("HeightMapData/", "heightField.raw", "heightField.jpg");

	m_pMap = pMap;
}

void cMainGame::Setup_UI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	{
		//m_pTexture = g_pTextureManager->GetTexture("UI/김태희.jpg");
	}
	{
		D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			"UI/김태희.jpg",
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,		//파일포맷, 잘못 읽어오면 이부분을 수정해야함
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_stImageInfo,
			NULL,
			&m_pTexture);
	}
}
void cMainGame::UI_Render()
{
	{
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		{
			static float F = 0.0f;
			F += 0.01f;
			//여기서 Z축 로테이션 하면 돌아감
		}
		D3DXMATRIXA16 matT, matR, matS, mat;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixTranslation(&matT, 0, 0, 0);
		D3DXMatrixRotationZ(&matR, D3DX_PI / 0.1f);

		mat = matR * matT;
		m_pSprite->SetTransform(&mat);
		///스프라이트만 트랜스폼 한다.
		///디바이스를 변경하면 연결된 모든게 변할 수 있음


		//RECT rc;	///출력 영역 지정
		//SetRect(&rc, 0, 0, 579, 381);
		//m_pSprite->Draw(m_pTexture,
		//	&rc,
		//	&D3DXVECTOR3(0, 0, 0),	///센터 지정
		//	&D3DXVECTOR3(100, 0, 0),	///포지션 지정
		//	D3DCOLOR_ARGB(255, 255, 255, 255));

		RECT rc;	///출력 영역 지정
		SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
		//-100으로 설정하면없는 부분에서 출력하려 하기 때문에
		//흰색이 더 채워지게 됨
		m_pSprite->Draw(m_pTexture,
			&rc,
			&D3DXVECTOR3(0, m_stImageInfo.Width / 2, m_stImageInfo.Height / 2),	///센터 지정
			&D3DXVECTOR3(0, m_stImageInfo.Width / 2, m_stImageInfo.Height / 2),	///포지션 지정
			D3DCOLOR_ARGB(120, 255, 255, 255));

		m_pSprite->End();
	}
}

