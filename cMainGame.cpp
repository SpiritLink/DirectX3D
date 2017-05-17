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

#define SPHERERADIUS 5.0f

cMainGame::cMainGame()
	: //m_pCubePC(NULL),
	m_pGrid(NULL),
	m_pCamera(NULL),
	m_pMap(NULL),
	m_pWoman(NULL),
	m_pFont(NULL),
	m_p3DText(NULL),
	m_pMeshSphere(NULL),
	m_pObjMesh(NULL),
	m_bSwitch(true)
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
	for (size_t i = 0; i < m_vecMap.size(); ++i)
		SAFE_DELETE(m_vecMap[i]);
	SAFE_RELEASE(m_pMeshSphere);
	SAFE_RELEASE(m_pObjMesh);
	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
		SAFE_RELEASE(m_vecObjMtlTex[i]);
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

	Text_Render();
	//Obj_Render();
	Mesh_Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);
	UINT nMessage = message;

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXVECTOR3 vRayPosition = m_pCamera->GetCamPosition();
	D3DXVECTOR3 vRayDirection;
	D3DXVECTOR3 vDestination;
	switch (message)
	{
	case WM_LBUTTONDOWN:
		vRayDirection = CalcPickingRayDirection();
		TransformRay(&vRayPosition, &vRayDirection, &matWorld);
		if (raySphereIntersectionTest(&vRayPosition, &vRayDirection, &m_vSphere))
		{
			if (m_bSwitch) m_bSwitch = false;
			else m_bSwitch = true;
		}
		/// 구와 충돌을 검사하는 함수 실행
		break;
	case WM_RBUTTONDOWN:
		vRayDirection = CalcPickingRayDirection();
		TransformRay(&vRayPosition, &vRayDirection, &matWorld);
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.y = HIWORD(lParam);
		g_ptMouse.x = LOWORD(lParam);
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
		lf.lfCharSet = DEFAULT_CHARSET;
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
		std::string sText = std::string("X:") + std::to_string(g_ptMouse.x);
		RECT rc;
		SetRect(&rc, 0, 40, 1, 0);
		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
	}

	{
		std::string sText = std::string("Y:") + std::to_string(g_ptMouse.y);
		RECT rc;
		SetRect(&rc, 0, 80, 1, 0);
		m_pFont->DrawTextA(NULL,
			sText.c_str(),
			sText.length(),
			&rc,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(255, 255, 0));
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
	m_vSphere.p = D3DXVECTOR3(0, 5, 10);
	m_vSphere.r = SPHERERADIUS;

	D3DXCreateSphere(g_pD3DDevice, SPHERERADIUS, 30, 30, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlSphere1, sizeof(D3DMATERIAL9));
	m_stMtlSphere1.Ambient = D3DXCOLOR(0.7f, 0.7F, 0.7F, 1.0F);
	m_stMtlSphere1.Specular = D3DXCOLOR(0.7f, 0.7F, 0.7F, 1.0F);
	m_stMtlSphere1.Diffuse = D3DXCOLOR(0.7f, 0.7F, 0.7F, 1.0F);

	ZeroMemory(&m_stMtlSphere2, sizeof(D3DMATERIAL9));
	m_stMtlSphere2.Ambient = D3DXCOLOR(0.7f, 0.0F, 0.0F, 1.0F);
	m_stMtlSphere2.Specular = D3DXCOLOR(0.7f, 0.0F, 0.0F, 1.0F);
	m_stMtlSphere2.Diffuse = D3DXCOLOR(0.7f, 0.0F, 0.0F, 1.0F);

	cObjLoader loadObj;
	loadObj.Load(m_vecMap, "obj", "Map.obj");
	m_pObjMesh = loadObj.LoadMesh(m_vecObjMtlTex, "obj", "Map.obj");
}

void cMainGame::Mesh_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;

	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld,
			0, 5, 10);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		if (m_bSwitch)
			g_pD3DDevice->SetMaterial(&m_stMtlSphere1);
		else
			g_pD3DDevice->SetMaterial(&m_stMtlSphere2);
		m_pMeshSphere->DrawSubset(0);
	}

	//{
	//	D3DXMatrixIdentity(&matS);
	//	D3DXMatrixIdentity(&matR);
	//	D3DXMatrixIdentity(&matWorld);
	//	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	//	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	//	matWorld = matS * matR;
	//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	//	for (size_t i = 0; i < m_vecObjMtlTex.size(); ++i)
	//	{
	//		g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
	//		g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
	//		m_pObjMesh->DrawSubset(i);
	//	}
	//}
}

/*-------------------------------------
* 스크린에서 투영창으로의 변환
*-------------------------------------
*/
float cMainGame::CalcProjectionX()
{
	D3DVIEWPORT9 stViewport;						//뷰포트 얻어오기
	ZeroMemory(&stViewport, sizeof(D3DVIEWPORT9));
	g_pD3DDevice->GetViewport(&stViewport);

	RECT rc;										//투영행렬 얻어오기
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0F, rc.right / (float)rc.bottom,
		1.0f, 1000.0f);
	float Width = stViewport.Width;
	float ViewportX = ((2.0f * g_ptMouse.x) / (float)Width) - 1.0f;

	float fProjectionX = ViewportX / (float)matProj._11;

	return fProjectionX;
}
/*-------------------------------------
* 스크린에서 투영창으로의 변환
*-------------------------------------
*/
float cMainGame::CalcProjectionY()
{
	D3DVIEWPORT9 stViewport;						//뷰포트 얻어오기
	ZeroMemory(&stViewport, sizeof(D3DVIEWPORT9));
	g_pD3DDevice->GetViewport(&stViewport);

	RECT rc;										//투영행렬 얻어오기
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0F, rc.right / (float)rc.bottom,
		1.0f, 1000.0f);
	float fHeight = stViewport.Height;
	float fViewportY = ((-2.0f * g_ptMouse.y) / (float)fHeight) + 1;

	float fProjectionY = fViewportY / (float)matProj._22;

	return fProjectionY;
}
/*-------------------------------------
 * 픽킹 광선의 계산
 *-------------------------------------
 */
D3DXVECTOR3 cMainGame::CalcPickingRayDirection()
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	D3DXMATRIX projection;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &projection);

	px = ((( 2.0f * g_ptMouse.x) / vp.Width ) - 1.0f) / projection(0, 0);
	py = (((-2.0f * g_ptMouse.y) / vp.Height) + 1.0f) / projection(1, 1);

	return D3DXVECTOR3(px, py, 1.0f);
}
/*-------------------------------------
 * 광선의 변환
 *-------------------------------------
 */
void cMainGame::TransformRay(D3DXVECTOR3 * rayPosition, D3DXVECTOR3 * rayDirection, D3DXMATRIX * matWorld)
{
	D3DXVec3TransformCoord(rayPosition, rayPosition, matWorld);		/// 광선의 원점을 변환
	D3DXVec3TransformNormal(rayDirection, rayDirection, matWorld);	/// 광선의 방향을 변환
	D3DXVec3Normalize(rayDirection, rayDirection);					/// 방향벡터 정규화
}

bool cMainGame::GridCollision(IN cGrid * m_pGrid, IN D3DXVECTOR3 vRayPosition, IN D3DXVECTOR3 vRayDirection,OUT D3DXVECTOR3* Destination)
{
	if (!m_pGrid) return false;

	D3DXVECTOR3 RayPosition = vRayPosition;
	D3DXVECTOR3 RayDirection = vRayDirection;
	for (size_t i = 0; i < m_pGrid->getVertex()->size(); i += 3)
	{
		float u, v, f;

		if (D3DXIntersectTri(&(*m_pGrid->getVertex())[i + 0].p,
			&(*m_pGrid->getVertex())[i + 1].p,
			&(*m_pGrid->getVertex())[i + 2].p,
			&RayPosition,
			&RayDirection,
			&u, &v, &f))
		{
			D3DXVECTOR3 P0 = (*m_pGrid->getVertex())[i + 0].p;
			D3DXVECTOR3 P1 = (*m_pGrid->getVertex())[i + 1].p;
			D3DXVECTOR3 P2 = (*m_pGrid->getVertex())[i + 2].p;
			(*Destination) = P0 + u * (P1 - P0) + v * (P2 - P0);
			return true;
		}
	}
	return false;
}
/*-------------------------------------
 * 광선 물체 교차
 *-------------------------------------
 */
bool cMainGame::raySphereIntersectionTest(D3DXVECTOR3 * rayPosition, D3DXVECTOR3 * rayDirection, ST_PR_VERTEX * sphere)
{
	D3DXVECTOR3 v = *rayPosition - sphere->p;

	float b = 2.0f * D3DXVec3Dot(rayDirection, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->r * sphere->r);

	// 판별식을 찾는다.
	float discriminant = (b * b) - (4.0f * c);

	// 가상의 수에 대한 테스트
	if (discriminant < 0.0f)
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// 해가 >= 0일 경우 구체를 교차하는 것이다.
	if (s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}
