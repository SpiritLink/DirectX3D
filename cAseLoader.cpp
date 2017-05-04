#include "stdafx.h"
#include "cAseLoader.h"
#include "cGroup.h"
#include "Asciitok.h"

cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{
}

void cAseLoader::Load(OUT std::vector<cGroup*>& vecGroup, IN char * szFolder, IN char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath += std::string("/") + std::string(szFile);
	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	int nCurrentCount;
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
			sscanf_s(szTemp, "%*s %d", &nCurrentCount);
		}

		if (keyWord == ID_AMBIENT)
		{
			float r, g, b;
			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_vecMaterial[nCurrentCount].Ambient.r = r;
			m_vecMaterial[nCurrentCount].Ambient.g = g;
			m_vecMaterial[nCurrentCount].Ambient.b = b;
			m_vecMaterial[nCurrentCount].Ambient.a = 1.0f;
		}
		if (keyWord == ID_DIFFUSE)
		{
			float r, g, b;
			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_vecMaterial[nCurrentCount].Diffuse.r = r;
			m_vecMaterial[nCurrentCount].Diffuse.g = g;
			m_vecMaterial[nCurrentCount].Diffuse.b = b;
			m_vecMaterial[nCurrentCount].Diffuse.a = 1.0f;
		}
		if (keyWord == ID_SPECULAR)
		{
			float r, g, b;
			sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
			m_vecMaterial[nCurrentCount].Specular.r = r;
			m_vecMaterial[nCurrentCount].Specular.g = g;
			m_vecMaterial[nCurrentCount].Specular.b = b;
			m_vecMaterial[nCurrentCount].Specular.a = 1.0f;
		}
		if (keyWord == ID_BITMAP)
		{
			char path[1024];
			sscanf_s(szTemp, "%*s %s", &path,1024);
			std::string sFullPath(path);
			sFullPath.pop_back();
			g_pTextureManager->GetTexture(sFullPath);
		}
	}
	
}
