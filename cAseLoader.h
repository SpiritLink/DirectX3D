#pragma once

class cGroup;

class cAseLoader
{
private:
	std::vector<D3DMATERIAL9> m_vecMaterial;
public:
	cAseLoader();
	~cAseLoader();
	void Load(OUT std::vector<cGroup*>& vecGroup, IN char* szFolder, IN char* szFile);
};

