#pragma once

class cWoman;

class cAseLoader
{
private:
	std::vector<D3DMATERIAL9> m_vecMaterial;
	std::map<std::string, cWoman*> m_vecWoman;
	std::map<int, std::string>	m_mapTexture;
public:
	cAseLoader();
	~cAseLoader();
	void Load(OUT cWoman** RootWoman, IN char* szFolder, IN char* szFile);
};

