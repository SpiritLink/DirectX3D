#include "stdafx.h"
#include "cAseLoader.h"
#include "cWoman.h"
#include "Asciitok.h"
#include "cMtlTex.h"
cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{
}

void cAseLoader::Load(OUT cWoman** RootWoman, IN char * szFolder, IN char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string("/") + std::string(szFile);
	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	
	int nIdx, nVertexNormal = 0;
	std::string sCurrentName;
	D3DXMATRIXA16 matRotate;
	matRotate.m[0][3] = 0;
	matRotate.m[1][3] = 0;
	matRotate.m[2][3] = 0;
	matRotate.m[3][3] = 1;

	std::vector<D3DXVECTOR3> vecVertex;
	std::vector<D3DXVECTOR3> vecTVERT;
	std::vector<ST_PNT_VERTEX> vecPNT;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024], szTemp2[1024];
		fgets(szTemp, 1024, fp);

		sscanf_s(szTemp, "%s %*s", &szTemp2,1024);
		std::string keyWord(szTemp2);

		/// MATERIAL_COUNT만큼 Material Vector크기 변경
		if (keyWord == ID_MATERIAL_COUNT)
		{
			int nCnt;
			sscanf_s(szTemp, "%*s %d", &nCnt);
			m_vecMaterial.resize(nCnt);
		}
		if (keyWord == ID_MATERIAL)
		{
			sscanf_s(szTemp, "%*s %d", &nIdx);
		}

		if (keyWord == ID_AMBIENT)
		{
			float r, g, b;
			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_vecMaterial[nIdx].Ambient.r = r;
			m_vecMaterial[nIdx].Ambient.g = g;
			m_vecMaterial[nIdx].Ambient.b = b;
			m_vecMaterial[nIdx].Ambient.a = 1.0f;
		}
		if (keyWord == ID_DIFFUSE)
		{
			float r, g, b;
			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_vecMaterial[nIdx].Diffuse.r = r;
			m_vecMaterial[nIdx].Diffuse.g = g;
			m_vecMaterial[nIdx].Diffuse.b = b;
			m_vecMaterial[nIdx].Diffuse.a = 1.0f;
		}
		if (keyWord == ID_SPECULAR)
		{
			float r, g, b;
			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_vecMaterial[nIdx].Specular.r = r;
			m_vecMaterial[nIdx].Specular.g = g;
			m_vecMaterial[nIdx].Specular.b = b;
			m_vecMaterial[nIdx].Specular.a = 1.0f;
		}
		if (keyWord == ID_BITMAP)
		{
			char path[1024];
			sscanf_s(szTemp, "%*s %s", &path,1024);
			std::string sFullPath(path);
			sFullPath.pop_back();
			g_pTextureManager->GetTexture(sFullPath);
		}

		if (keyWord == ID_NODE_NAME)
		{
			char name1[1024]{ 0, }, name2[1024] = { 0, }, name3[1024] = { 0, };
			sscanf_s(szTemp, "%*s%s%s%s", &name1, 1024, &name2, 1024, &name3, 1024);
			std::string sFirstName(name1);
			std::string sMiddleName(name2);
			std::string sLastName(name3);

			sFirstName.erase(0, 1);
			if (sMiddleName.size() <= 0)
				if (sFirstName.size())sFirstName.pop_back();
			if (sLastName.size() <= 0)
				if (sMiddleName.size())sMiddleName.pop_back();
			if (sLastName.size())
				sLastName.pop_back();
			std::string sFullName = sFirstName + sMiddleName + sLastName;

			if (m_vecWoman[sFullName] == NULL)
				m_vecWoman[sFullName] = new cWoman;
			if (*RootWoman == NULL)
				*RootWoman = m_vecWoman[sFullName];
			sCurrentName = sFullName;
		}

		if (keyWord == ID_NODE_PARENT)
		{
			char name1[1024]{ 0, }, name2[1024] = { 0, }, name3[1024] = { 0, };
			sscanf_s(szTemp, "%*s%s%s%s", &name1, 1024, &name2, 1024, &name3, 1024);
			std::string sFirstName(name1);
			std::string sMiddleName(name2);
			std::string sLastName(name3);
			
			sFirstName.erase(0, 1);
			if (sMiddleName.size() <= 0)
				if (sFirstName.size())sFirstName.pop_back();
			if (sLastName.size() <= 0)
				if (sMiddleName.size())sMiddleName.pop_back();
			if (sLastName.size())
				sLastName.pop_back();

			std::string sFullName = sFirstName + sMiddleName + sLastName;

			m_vecWoman[sFullName]->addChild(m_vecWoman[sCurrentName]);
		}

		if (keyWord == ID_INHERIT_POS)
		{
			int x, y, z;
			sscanf_s(szTemp, "%*s %d %d %d", &x, &y, &z);
			m_vecWoman[sCurrentName]->SetLocalPosition(D3DXVECTOR3(x, y, z));
		}

		if (keyWord == ID_TM_ROW0)
		{
			float x, y, z;
			sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
			matRotate.m[0][0] = x;
			matRotate.m[0][1] = y;
			matRotate.m[0][2] = z;
		}

		if (keyWord == ID_TM_ROW1)
		{
			float x, y, z;
			sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
			matRotate.m[1][0] = x;
			matRotate.m[1][1] = y;
			matRotate.m[1][2] = z;
		}

		if (keyWord == ID_TM_ROW2)
		{
			float x, y, z;
			sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
			matRotate.m[2][0] = x;
			matRotate.m[2][1] = y;
			matRotate.m[2][2] = z;
		}

		if (keyWord == ID_TM_ROW3)
		{
			float x, y, z;
			sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
			matRotate.m[3][0] = x;
			matRotate.m[3][1] = y;
			matRotate.m[3][2] = z;
		}
		
		if (keyWord == ID_MESH_NUMVERTEX)
		{
			int size;
			sscanf_s(szTemp, "%*s %d", &size);
			vecVertex.clear();
			vecVertex.resize(size);
		}

		if (keyWord == ID_MESH_NUMFACES)
		{
			int size;
			sscanf_s(szTemp, "%*s %d", &size);
			m_vecWoman[sCurrentName]->GetVertex().resize(size * 3);
		}
		if (keyWord == ID_MESH_VERTEX)
		{
			int idx;
			float x, y, z;
			sscanf_s(szTemp, "%*s %d %f %f %f", &idx, &x, &y, &z);
			vecVertex[idx] = D3DXVECTOR3(x, y, z);
		}

		if (keyWord == ID_MESH_FACE)
		{
			int idx,A, B, C;
			sscanf_s(szTemp, "%*s %d: A: %d B: %d C: %d",&idx, &A, &B, &C);
			m_vecWoman[sCurrentName]->GetVertex()[(idx * 3) + 0].p = vecVertex[A];
			m_vecWoman[sCurrentName]->GetVertex()[(idx * 3) + 1].p = vecVertex[B];
			m_vecWoman[sCurrentName]->GetVertex()[(idx * 3) + 2].p = vecVertex[C];
		}
		if (keyWord == ID_MESH_FACENORMAL)
		{
			sscanf_s(szTemp, "%*s %d", &nIdx);
			nVertexNormal = 0;
		}
		if (keyWord == ID_MESH_VERTEXNORMAL)
		{
			int tempIdx;
			float x, y, z;
			sscanf_s(szTemp, "%*s %d %f %f %f", &tempIdx, &x, &y, &z);
			m_vecWoman[sCurrentName]->GetVertex()[nIdx * 3 + nVertexNormal].n = D3DXVECTOR3(x, y, z);
			++nVertexNormal;
		}

		if (keyWord == ID_MESH_NUMTVERTEX)
		{
			int size;
			sscanf_s(szTemp, "%*s %d", &size);
			vecTVERT.clear();
			vecTVERT.resize(size);
		}
		if (keyWord == ID_MESH_TVERT)
		{
			int tempIdx;
			float x, y, z;
			sscanf_s(szTemp, "%*s%d%f%f%f",&tempIdx, &x, &y, &z);
			vecTVERT[tempIdx] = D3DXVECTOR3(x, y, z);
		}
		if (keyWord == ID_MESH_TFACE)
		{
			int tempidx,x, y, z;
			sscanf_s(szTemp, "%*s %d %d %d %d", &tempidx, &x, &y, &z);
			m_vecWoman[sCurrentName]->GetVertex()[tempidx * 3 + 0].n = vecTVERT[x];
			m_vecWoman[sCurrentName]->GetVertex()[tempidx * 3 + 1].n = vecTVERT[y];
			m_vecWoman[sCurrentName]->GetVertex()[tempidx * 3 + 2].n = vecTVERT[z];
		}

		if (keyWord == ID_MATERIAL_REF)
		{
			int idx = 0;
			sscanf_s(szTemp, "%*s %d", &idx);
			if (m_vecWoman[sCurrentName]->GetMtlTex() == NULL)
				m_vecWoman[sCurrentName]->SetMtlTex(new cMtlTex);
			m_vecWoman[sCurrentName]->GetMtlTex()->SetMaterial(m_vecMaterial[idx]);
		}
	}

	int D = 3;
}
