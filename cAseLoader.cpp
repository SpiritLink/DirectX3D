#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"
cAseLoader::cAseLoader()
	: m_fp(NULL)
{
}


cAseLoader::~cAseLoader()
{
}

cFrame * cAseLoader::Load(IN char * szFullPath)
{
	fopen_s(&m_fp, szFullPath, "r");

	cFrame* pRoot = NULL;

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			SkipBlock();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame*	pFrame = ProcessGEOMOBJECT();
			if (pRoot == NULL)
			{
				pRoot = pFrame;
				Set_SceneFrame(pRoot);
			}
		}
	}
	fclose(m_fp);

	for each(auto p in m_vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	pRoot->CalcOriginalLocalTM(NULL);
	return pRoot;
}

char * cAseLoader::GetToken()
{
	int nReadCnt = 0;
	bool isQuote = false;

	while (true)
	{
		char c = fgetc(m_fp);
		if (feof(m_fp)) break;

		if (c == '\"')
		{
			if (isQuote) break;
			isQuote = true;
			continue;
		}

		if (!isQuote && IsWhite(c))
		{
			if (nReadCnt == 0)
				continue;
			else
				break;
		}

		m_szToken[nReadCnt++] = c;
	}
	if (nReadCnt == 0)
		return NULL;

	m_szToken[nReadCnt] = '\0';

	return m_szToken;
}

int cAseLoader::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return (float)atof(GetToken());
}

bool cAseLoader::IsWhite(IN char c)
{
	return c < 33;
}

bool cAseLoader::IsEqual(IN char * str1, IN char * str2)
{
	return strcmp(str1, str2) == 0;
}

void cAseLoader::SkipBlock()
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for each(auto p in m_vecMtlTex)
			{
				SAFE_RELEASE(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			int nIndex = GetInteger();
			m_vecMtlTex[nIndex] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[nIndex]);
		}
	} while (nLevel > 0);

}

void cAseLoader::ProcessMATERIAL(OUT cMtlTex * pMtlTex)
{
	D3DMATERIAL9 stMtl;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));

	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtlTex);
		}
	} while (nLevel > 0);

	pMtlTex->SetMaterial(stMtl);
}

void cAseLoader::ProcessMAP_DIFFUSE(OUT cMtlTex * pMtlTex)
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			szToken = GetToken();
			pMtlTex->SetTexture(g_pTextureManager->GetTexture(szToken));
		}
	} while (nLevel > 0);
}

cFrame * cAseLoader::ProcessGEOMOBJECT()
{
	cFrame* pFrame = new cFrame;

	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetInteger();
			pFrame->SetMtlTex(m_vecMtlTex[nMtlIndex]);
		}
	} while (nLevel > 0);

	return pFrame;
}

void cAseLoader::ProcessMESH(OUT cFrame * pFrame)
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
}

void cAseLoader::ProcessMESH_VERTEX_LIST(OUT std::vector<D3DXVECTOR3>& vecV)
{
}

void cAseLoader::ProcessMESH_FACE_LIST(OUT std::vector<ST_PNT_VERTEX>& vecVertex, IN std::vector<D3DXVECTOR3> vecV)
{
}

void cAseLoader::ProcessMESH_TVERTLISE(OUT std::vector<D3DXVECTOR2>& vecT)
{
}

void cAseLoader::ProcessMESH_TFACELIST(OUT std::vector<ST_PNT_VERTEX> vecVertex, IN std::vector<D3DXVECTOR2>& vecVT)
{
}

void cAseLoader::ProcessMESH_NORMALS(OUT std::vector<ST_PNT_VERTEX>& vecVertex)
{
}

void cAseLoader::ProcessNODE_TM(OUT cFrame * pFrame)
{
}

void cAseLoader::Set_SceneFrame(OUT cFrame * pRoot)
{
}
