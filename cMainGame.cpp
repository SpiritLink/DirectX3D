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
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIButton.h"

enum
{
	E_BUTTON_OK = 11,
	E_BUTTON_CANCEL,
	E_BUTTON_EXIT,
	E_TEXT_VIEW,
};

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
	m_pSprite(NULL),
	m_pUIRoot(NULL),
	m_pZealot(NULL)
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
	SAFE_RELEASE(m_pSprite);
	if(m_pUIRoot)
		m_pUIRoot->Destroy();
	SAFE_DELETE(m_pUIRoot);
	SAFE_RELEASE(m_pZealot);

	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	g_pTextManager->GetFont("NanumBarunGothic");
	m_pGrid = new cGrid;
	m_pGrid->Setup();

	//m_pWoman = new cWoman;
	//m_pWoman->Setup();
	Load_Surface();
	{
		cCubeMan* pCubeMan = new cCubeMan;
		pCubeMan->Setup();
		m_pCubeMan = pCubeMan;
		//Setup_HeightMap();
	}

	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	Set_Light();
	Setup_MeshObject();
	Setup_Button();
	Setup_Xfile();
}

void cMainGame::Update()
{
	if (m_pUIRoot)
		m_pUIRoot->Update();
	if (m_pCamera) 
		m_pCamera->Update();
	if (m_pWoman)
		m_pWoman->update();
	if (m_pCubeMan)
		m_pCubeMan->Update(NULL);
}

void cMainGame::Render()
{
	//g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);
	//g_pD3DDevice->BeginScene();
	////if (m_pGrid) m_pGrid->Render();
	////if (m_pMap)
	//	//m_pMap->Render();
	////if (m_pWoman) 
	////	m_pWoman->Render();
	//if (m_pCubeMan) 
	//	m_pCubeMan->Render();
	////Obj_Render();
	//Mesh_Render();
	////PickingObj_Render();
	//m_pUIRoot->Render(m_pSprite);

	//g_pTextManager->TextRender("FPS:", &g_nFrameCount, 0, 0, 0, 255, 0, INT_POINTER);
	//g_pTextManager->TextRender("MouseX:", &g_ptMouse.x, 0, 30, INT_POINTER);
	//g_pTextManager->TextRender("MouseY:", &g_ptMouse.y, 0, 60, INT_POINTER);
	//g_pD3DDevice->EndScene();
	//g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	Display(0.1f);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	int nX = m_pUIRoot->GetPosition().x;
	int nY = m_pUIRoot->GetPosition().y;
	SetRect(&rc, nX, nY, nX + m_pUIRoot->GetSize().nWidth, nY + m_pUIRoot->GetSize().nHeight);
	if (PtInRect(&rc, g_ptMouse)) return;

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

void cMainGame::Setup_Button()
{
	cUIImageView * pImageView = new cUIImageView;
	pImageView->SetPosition(0, 0, 0);
	pImageView->SetTexture("UI/panel-info.png");
	m_pUIRoot = pImageView;

	cUITextView * pTextView = new cUITextView;
	pTextView->SetText("좀비출현");
	pTextView->SetSize(ST_SIZEN(300, 200));
	pTextView->SetPosition(100, 100);
	pTextView->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	pTextView->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	pTextView->SetTag(E_TEXT_VIEW);
	m_pUIRoot->AddChild(pTextView);

	cUIButton * pButtonOK = new cUIButton;
	pButtonOK->SetTexture(
		"UI/btn-med-up.png",
		"UI/btn-med-over.png",
		"UI/btn-med-down.png");
	pButtonOK->SetPosition(135, 330);
	pButtonOK->SetDelegate(this);
	pButtonOK->SetTag(E_BUTTON_OK);
	m_pUIRoot->AddChild(pButtonOK);
}

void cMainGame::OnClick(cUIButton * pSender)
{
	cUITextView* pTextView = (cUITextView*)m_pUIRoot->FindChildByTag(E_TEXT_VIEW);

	if (pSender->GetTag() == E_BUTTON_OK)
	{
		pTextView->SetText("확인");
	}
	else
	{
		pTextView->SetText("기타");
	}
}

bool cMainGame::Setup_Xfile()
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;
	hr = D3DXLoadMeshFromX(
		"Xfile/Zealot.X",
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_pZealot);

	if (FAILED(hr))
	{
		::MessageBox(0, "D3DXLoadMeshFromX () - FAILED", 0, 0);
		return false;
	}

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
		for (int i = 0; i < numMtrls; i++)
		{
			// MatD3D 속성은 로드될 때 ambient 값을 가지지 않으므로
			// 지금 이를 지정한다.
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// i번재 재질을 저장한다.
			Mtrls.push_back(mtrls[i].MatD3D);

			// i번째 재질에 연결된 텍스처가 있는지를 확인한다.
			if (mtrls[i].pTextureFilename != 0)
			{
				// 만약 그렇다면 i번째 서브셋을 위한 텍스처를 읽어들인다.
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					g_pD3DDevice,
					mtrls[i].pTextureFilename,
					&tex);

				// 읽어들인 텍스처를 저장한다.
				Textures.push_back(tex);
			}
			else
			{
				// i번째 서브셋에 텍스쳐가 없다.
				Textures.push_back(0);
			}
		}
	}
	SAFE_RELEASE(mtrlBuffer);

	return true;
}

bool cMainGame::Display(float timeDelta)
{
	if (g_pD3DDevice)
	{
		static float y = 0.0f;
		D3DXMATRIX yRot;
		D3DXMatrixRotationY(&yRot, y);
		y += timeDelta;

		if (y >= 6.28f)
			y = 0.0f;

		D3DXMATRIX World = yRot;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &World);

		// 렌더링
		
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0xffffffff, 1.0f, 0);

		g_pD3DDevice->BeginScene();

		for (int i = 0; i < Mtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&Mtrls[i]);
			g_pD3DDevice->SetTexture(0, Textures[i]);
			m_pZealot->DrawSubset(i);
		}

		g_pD3DDevice->EndScene();
		g_pD3DDevice->Present(0, 0, 0, 0);
	}
	return true;
}
