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

#include "cSkinnedMesh.h"

#include "cFrustum.h"

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
	: m_pGrid(NULL)
	, m_pCamera(NULL)
	, m_pMap(NULL)
	, m_pWoman(NULL)
	, m_pObjMesh(NULL)
	, m_bSwitch(true)
	, m_pCubeMan(NULL)
	, m_pSprite(NULL)
	, m_pUIRoot(NULL)
	, m_pZealot(NULL)
	, m_pSkinnedMesh(NULL)
	, nAnimIndex(0)
	, m_pFrustrum(NULL)
	, m_pSphere(NULL)
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pSphere, NULL);
	for (int i = 0; i < 1000; ++i)
	{
		ST_SPHERE stTemp;
		stTemp.fRadius = 0.5f;
		stTemp.vCenter = D3DXVECTOR3(0, 5, 0);
		m_vecStSphere.push_back(stTemp);
	}
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pWoman);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pCubeMan);
	SAFE_DELETE(m_pUIRoot);
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pFrustrum);

	SAFE_RELEASE(m_pSprite);
	if(m_pUIRoot)
		m_pUIRoot->Destroy();
	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		SAFE_RELEASE(m_vecObjMtlTex[i]);
	SAFE_RELEASE(m_pZealot);
	SAFE_RELEASE(m_pObjMesh);
	SAFE_RELEASE(m_pSphere);

	g_pTextManager->Destroy();
	g_pTextureManager->Destroy();
	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
	g_pTextManager->GetFont("NanumBarunGothic");
	m_pCamera = new cCamera;
	m_pCamera->Setup(NULL);

	m_pFrustrum = new cFrustum;
	m_pFrustrum->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	//m_pWoman = new cWoman;
	//m_pWoman->Setup();
	Load_Surface();
	//{
	//	cCubeMan* pCubeMan = new cCubeMan;
	//	pCubeMan->Setup();
	//	m_pCubeMan = pCubeMan;
	//	//Setup_HeightMap();
	//}


	Set_Light();
	Setup_MeshObject();
	Setup_Button();

	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup("Zealot", "Zealot.x");
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
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
	if (m_pFrustrum)
		m_pFrustrum->Update();

	Keyboard();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);
	g_pD3DDevice->BeginScene();
	if (m_pGrid) m_pGrid->Render();
	//if (m_pMap)
		//m_pMap->Render();
	//if (m_pWoman) 
	//	m_pWoman->Render();
	if (m_pCubeMan) 
		m_pCubeMan->Render();
	//Obj_Render();
	Mesh_Render();
	//PickingObj_Render();
	m_pUIRoot->Render(m_pSprite);
	if (m_pSkinnedMesh)	m_pSkinnedMesh->Render(NULL);
	DrawSphere();

	g_pTextManager->TextRender("FPS:", &g_nFrameCount, 0, 0, 0, 255, 0, INT_POINTER);
	g_pTextManager->TextRender("MouseX:", &g_ptMouse.x, 0, 30, INT_POINTER);
	g_pTextManager->TextRender("MouseY:", &g_ptMouse.y, 0, 60, INT_POINTER);
	for (int i = 0; i < m_vecChar.size(); ++i)
	{
		g_pTextManager->TextRender(std::to_string(m_vecChar[i]), NULL, i * 20, 100,255,0,0, NULL_POINTER);
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	//Display(0.1f);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	int nX = m_pUIRoot->GetPosition().x;
	int nY = m_pUIRoot->GetPosition().y;
	SetRect(&rc, nX, nY, nX + m_pUIRoot->GetSize().nWidth, nY + m_pUIRoot->GetSize().nHeight);
	if (PtInRect(&rc, g_ptMouse)) return;

	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_RBUTTONDOWN:
		if (m_pSkinnedMesh)
		{
			nAnimIndex++;
			//m_pSkinnedMesh->SetAnimationIndex(nAnimIndex);
			m_pSkinnedMesh->SetAnimationIndexBlend(nAnimIndex);
		}
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

void cMainGame::Keyboard()
{
	// IP의 주소가 전부 들어왔으면 더이상 push_back하지 않는다.
	// IP주소는 일반적으로 12자리 이다.
	if (GetAsyncKeyState(VK_BACK) & 0x0001)				///BackSpace 누르면 Pop_back
	{
		if(!m_vecChar.empty()) m_vecChar.pop_back();
	}

	if (m_vecChar.size() >= 12)
	{
		while (m_vecChar.size() > 12)
			m_vecChar.pop_back();
	}
	if (GetAsyncKeyState('0') & 0x0001 || GetAsyncKeyState(VK_NUMPAD0) & 0x0001)
	{
		m_vecChar.push_back(0);
	}
	if (GetAsyncKeyState('1') & 0x0001 || GetAsyncKeyState(VK_NUMPAD1) & 0x0001)
	{
		m_vecChar.push_back(1);
	}
	if (GetAsyncKeyState('2') & 0x0001 || GetAsyncKeyState(VK_NUMPAD2) & 0x0001)
	{
		m_vecChar.push_back(2);
	}	
	if (GetAsyncKeyState('3') & 0x0001 || GetAsyncKeyState(VK_NUMPAD3) & 0x0001)
	{
		m_vecChar.push_back(3);
	}	
	if (GetAsyncKeyState('4') & 0x0001 || GetAsyncKeyState(VK_NUMPAD4) & 0x0001)
	{
		m_vecChar.push_back(4);
	}	
	if (GetAsyncKeyState('5') & 0x0001 || GetAsyncKeyState(VK_NUMPAD5) & 0x0001)
	{
		m_vecChar.push_back(5);
	}	
	if (GetAsyncKeyState('6') & 0x0001 || GetAsyncKeyState(VK_NUMPAD6) & 0x0001)
	{
		m_vecChar.push_back(6);
	}
	if (GetAsyncKeyState('7') & 0x0001 || GetAsyncKeyState(VK_NUMPAD7) & 0x0001)
	{
		m_vecChar.push_back(7);
	}
	if (GetAsyncKeyState('8') & 0x0001 || GetAsyncKeyState(VK_NUMPAD8) & 0x0001)
	{
		m_vecChar.push_back(8);
	}
	if (GetAsyncKeyState('9') & 0x0001 || GetAsyncKeyState(VK_NUMPAD9) & 0x0001)
	{
		m_vecChar.push_back(9);
	}
	// 주소를 저장한다.
}

void cMainGame::DrawSphere()
{
	D3DXMATRIXA16 matWorld, matS, matR;

	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
	matWorld = matS * matR;
	D3DXMatrixTranslation(&matWorld, 0, 5, 0);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtlNone);
	for (int i = 0; i < m_vecStSphere.size(); ++i)
	{
		if (m_pFrustrum->IsIn(&m_vecStSphere[i]))
		{
			for (int i = 0; i < 100; ++i)
			{
				m_pSphere->DrawSubset(0);
			}
		}
	}
}
