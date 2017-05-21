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
#define SPHERERADIUS 0.5f
#define RAWSIZE 257
#define TILESIZE 256


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
	m_bSwitch(true),
	m_pRawMap(NULL)
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
	SAFE_RELEASE(m_pRawMap);
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

	m_vecRawMap = Setup_RawMap("HeightMapData","HeightMap.raw");
	Set_Light();
	Create_Font();
	Setup_MeshObject();
	Setup_PickingObj();
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


	//if (m_pGrid) m_pGrid->Render();
	if (m_pWoman) m_pWoman->Render();

	//Text_Render();
	//Obj_Render();
	Mesh_Render();
	//PickingObj_Render();
	RawMap_Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera) m_pCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));
			for (size_t i = 0; i < m_vecSphere.size(); i++)
				m_vecSphere[i].isPicked = r.IsPicked(&m_vecSphere[i]);
		}
		break;
	case WM_RBUTTONDOWN:
		{
		cRay r = cRay::RayAtWorldSpace(LOWORD(lParam), HIWORD(lParam));

			for (size_t i = 0; i < m_vecPlaneVertex.size(); i += 3)
			{
				D3DXVECTOR3 v(0, 0, 0);
				if (r.IntersectTri(m_vecPlaneVertex[i + 0].p,
					m_vecPlaneVertex[i + 1].p,
					m_vecPlaneVertex[i + 2].p,
					v
				))
				{
					m_vPickedPosition = v;
				}
			}
		}
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

	m_pMap = new cObjMap("HeightMapData", "HeightMap.raw", &matWorld);
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
		//m_p3DText->DrawSubset(0);
	}
}

void cMainGame::Setup_MeshObject()
{
	m_pRawTexture = g_pTextureManager->GetTexture("HeightMapData/terrain.jpg");

	m_vSphere.vCenter = D3DXVECTOR3(0, 5, 10);
	m_vSphere.fRadius = SPHERERADIUS;

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

std::vector<ST_PNT_VERTEX> cMainGame::Setup_RawMap(IN char * szFolder, IN char * szFile)
{
	cRawLoader rLoader;
	std::vector<unsigned int> vecRawData;
	vecRawData = rLoader.LoadRawData(szFolder, szFile);

	ST_PNT_VERTEX p;
	p.n = D3DXVECTOR3(0, 1, 0);	///법선 벡터 디폴트값
	p.p = D3DXVECTOR3(0, 0, 0);	///x, y, z 값을 바꿔줘야함
	p.t = D3DXVECTOR2(0, 0);	/// 텍스쳐 0 부터 1까지의 값

	///맵 좌표 생성
	std::vector<ST_PNT_VERTEX> vecVertex;
	for (int i = 0; i < RAWSIZE; ++i)
	{
		for (int j = 0; j < RAWSIZE; ++j)
		{
			p.p.x = j;
			p.p.y = vecRawData[j + i * RAWSIZE] / (float)10.0f;

			p.p.z = i;

			if (j == 0)
				p.t.x = 0;
			else
				p.t.x = j / (float)RAWSIZE;

			if (i == 0)
				p.t.y = 0;
			else
				p.t.y = (i / (float)RAWSIZE);

			vecVertex.push_back(p);
		}
	}

	///맵 법선벡터 재설정
	for (int i = 1; i < TILESIZE; ++i)
	{
		for (int j = 1; j < TILESIZE; ++j)
		{
			D3DXVECTOR3 vHorizon, vVertical, vn;
			vHorizon = vecVertex[i + (j * RAWSIZE) + 1].p - vecVertex[i + (j * RAWSIZE) - 1].p;				///수평
			vVertical = vecVertex[i + (j * RAWSIZE) - RAWSIZE].p - vecVertex[i + (j * RAWSIZE) + RAWSIZE].p;	///수직
			D3DXVec3Normalize(&vHorizon, &vHorizon);	///수평 정규화
			D3DXVec3Normalize(&vVertical, &vVertical);	///수직 정규화
			D3DXVec3Cross(&vn, &vHorizon, &vVertical);	///외적
			D3DXVec3Normalize(&vn, &vn);				///법선벡터 정규화
			vecVertex[i + j * RAWSIZE].n = vn;		///대입
		}
	}

	///삼각형 그리기 순서에 따른 ST_PNT_VERTEX삽입
	std::vector<ST_PNT_VERTEX> vecIndex;
	for (int i = 0; i < TILESIZE; ++i)		///x
	{
		for (int j = 0; j < TILESIZE; ++j)	///y
		{
			unsigned int k;
			k = j + (i * RAWSIZE);					vecIndex.push_back(vecVertex[k]);	///왼쪽 아래
			k = j + (i * RAWSIZE) + RAWSIZE;		vecIndex.push_back(vecVertex[k]);	///왼쪽 위
			k = j + (i * RAWSIZE) + 1 + RAWSIZE;	vecIndex.push_back(vecVertex[k]);	///오른쪽 위

			k = j + i * RAWSIZE;					vecIndex.push_back(vecVertex[k]);	///왼쪽 아래
			k = j + (i * RAWSIZE) + 1 + RAWSIZE;	vecIndex.push_back(vecVertex[k]);	///오른쪽 위
			k = j + (i * RAWSIZE) + 1;				vecIndex.push_back(vecVertex[k]);	///오른쪽 아래
		}
	}
	return vecIndex;
}


void cMainGame::Mesh_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;

	{
		//D3DXMatrixIdentity(&matWorld);
		//D3DXMatrixIdentity(&matS);
		//D3DXMatrixIdentity(&matR);
		//D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		//matWorld = matS * matR;
		//D3DXMatrixTranslation(&matWorld,
		//	0, 5, 10);
		//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		//if (m_bSwitch)
		//	g_pD3DDevice->SetMaterial(&m_stMtlSphere1);
		//else
		//	g_pD3DDevice->SetMaterial(&m_stMtlSphere2);
		//m_pMeshSphere->DrawSubset(0);
	}

	if(m_pRawMap)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		matWorld = matS * matR;
		D3DXMatrixTranslation(&matWorld, 0, 0, 0);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlPlane);
		g_pD3DDevice->SetTexture(0, m_pRawTexture);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pRawMap->DrawSubset(0);

		int a = m_pRawMap->GetNumFaces();
		int b = m_pRawMap->GetNumVertices();
		int c = 1;
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

void cMainGame::RawMap_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	matWorld = matS * matR;
	D3DXMatrixTranslation(&matWorld, 0, 0, 0);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtlPlane);
	g_pD3DDevice->SetTexture(0, m_pRawTexture);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST, 
		m_vecRawMap.size() / 3,
		&m_vecRawMap[0], sizeof(ST_PNT_VERTEX));

}


/*-------------------------------------
 * 광선 그리드 교차
 *-------------------------------------
 */
bool cMainGame::GridCollision(IN cGrid * m_pGrid, IN D3DXVECTOR3* vRayPosition, IN D3DXVECTOR3* vRayDirection,OUT D3DXVECTOR3* Destination)
{
	if (!m_pGrid) return false;

	for (size_t i = 0; i < m_pGrid->getVertex().size() ; i += 3)
	{
		float u, v, f;

		D3DXVECTOR3 P0 = m_pGrid->getVertex()[i + 0].p;
		D3DXVECTOR3 P1 = m_pGrid->getVertex()[i + 1].p;
		D3DXVECTOR3 P2 = m_pGrid->getVertex()[i + 2].p;
		if (D3DXIntersectTri(
			&P0,
			&P1,
			&P2,
			vRayPosition,
			vRayDirection,
			&u, &v, &f))
		{
			(*Destination) = P0 + (u * (P1 - P0)) + (v * (P2 - P0));
			return true;
		}
	}
	return false;
}

void cMainGame::Setup_PickingObj()
{
	for (int i = 0; i <= 10; i++)
	{
		ST_SPHERE s;
		s.fRadius = 0.5f;
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i);
		m_vecSphere.push_back(s);
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(-10, 0, +10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(+10, 0, +10); m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(+10, 0, +10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(+10, 0, -10); m_vecPlaneVertex.push_back(v);
}

void cMainGame::PickingObj_Render()
{
	D3DXMATRIXA16 matWorld;
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtlPlane);
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2,
		&m_vecPlaneVertex[0], sizeof(ST_PN_VERTEX));
	
	for (int i = 0; i < m_vecSphere.size(); ++i)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere[i].vCenter.x;
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(m_vecSphere[i].isPicked ?
			&m_stMtlPicked : &m_stMtlNone);

		m_pMeshSphere->DrawSubset(0);
	}

	g_pD3DDevice->SetMaterial(&m_stMtlNone);
	D3DXMatrixTranslation(&matWorld,
		m_vPickedPosition.x,
		m_vPickedPosition.y,
		m_vPickedPosition.z
		);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMeshSphere->DrawSubset(0);
}
