#include "stdafx.h"
#include "cObjLoader.h"
#include "cMtlTex.h"	// << :
#include "cGroup.h"		// >> :

cObjLoader::cObjLoader()
{
}

cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(OUT std::vector<cGroup*>& vecGroup, IN char * szFolder, IN char * szFile)
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<ST_PNT_VERTEX> vecVertex;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if(szTemp[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if(szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z ;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}

	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapMtlTex.clear();
	for (size_t i = 0; i < vecGroup.size(); ++i)
	{
		vecGroup[i]->BuildVertexBuffer();
	}
}

void cObjLoader::LoadMtlLib(char * szFolder, char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/")+ std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;
		
		if (szTemp[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);

			if (m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
				m_mapMtlTex[sMtlName] = new cMtlTex;
		}
		else if (szTemp[0] == 'K')
		{
			if (szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			else if (szTemp[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if (szTemp[1] == 's')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if (szTemp[0] == 'd')
		{
			float d;
			sscanf_s(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		else if (szTemp[0] == 'm')
		{
			char szTexFile[1024];
			sscanf_s(szTemp, "%*s %s", szTexFile, 1024);
			sFullPath = std::string(szFolder);
			sFullPath += (std::string("/") + std::string(szTexFile));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
		}
	}

	fclose(fp);
}

void cObjLoader::LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface, IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pMat)
{
	std::vector<D3DXVECTOR3> vecV;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);
			for (int i = 0; i < 3; ++i)
			{
				vecSurface.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}

	fclose(fp);

	if (pMat)
	{
		for (size_t i = 0; i < vecSurface.size(); ++i)
		{
			D3DXVec3TransformCoord(&vecSurface[i], &vecSurface[i], pMat);
		}
	}
}

LPD3DXMESH cObjLoader::LoadMesh(OUT std::vector<cMtlTex*>& vecMtlTex, IN char * szFolder, IN char * szFile)
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;

	LPD3DXMESH stMesh;
	stMesh = NULL;

	int nSubsetIndex = 0;
	int nCurrentSubset = 0;
	std::map<std::string, int> mapMtlTexIndex;
	std::vector<std::vector<ST_PNT_VERTEX>> VecInVecVertex;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE * fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string sMtlName;

	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
			continue;

		if (szTemp[0] == 'm')
		{
			for each(auto it in m_mapMtlTex)
			{
				SAFE_RELEASE(it.second);
			}
			m_mapMtlTex.clear();

			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);
			LoadMtlLib(szFolder, szMtlFile);
			for each(auto it in m_mapMtlTex)
			{
				vecMtlTex.push_back(it.second);
				mapMtlTexIndex.insert(make_pair(it.first, nSubsetIndex));
				++nSubsetIndex;
			}
			VecInVecVertex.resize(nSubsetIndex);
		}
		else if (szTemp[0] == 'g')
		{
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = std::string(szMtlName);
			nCurrentSubset = mapMtlTexIndex[szMtlName];
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				VecInVecVertex[nCurrentSubset].push_back(v);
			}
		}
	}

	fclose(fp);

	int nNumFaces = 0;
	for (int i = 0; i < VecInVecVertex.size(); ++i)
	{
		nNumFaces += VecInVecVertex[i].size() / 3;
	}

	D3DXCreateMeshFVF(nNumFaces, vecV.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &stMesh);

	for (size_t i = 0; i < VecInVecVertex.size(); ++i)
	{
		ST_PNT_VERTEX* pVertex = 0;
		stMesh->LockVertexBuffer(i, (void**)pVertex);
		memcpy(pVertex, &VecInVecVertex[i][0], VecInVecVertex[i].size() * sizeof(ST_PNT_VERTEX));
		stMesh->UnlockVertexBuffer();

		std::vector<WORD*> vecDword;
		vecDword.resize(VecInVecVertex[i].size());
		for (size_t j = 0; j < VecInVecVertex[i].size(); ++j)
			*vecDword[j] = (WORD)j;
		LPVOID* pIndex = 0;
		stMesh->LockIndexBuffer(i, pIndex);
		memcpy(pIndex, &vecDword[0], vecDword.size() * sizeof(WORD));
		stMesh->UnlockIndexBuffer();

		DWORD* pAttribute = 0;
		stMesh->LockAttributeBuffer(i, &pAttribute);
		for (size_t k = 0; k < VecInVecVertex[i].size(); ++k)
		{
			pAttribute[k] = i;
		}
		stMesh->UnlockAttributeBuffer();
		
	}

	for each(auto it in m_mapMtlTex)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapMtlTex.clear();

	return stMesh;
}
