#pragma once

class cWoman;

class cAseLoader
{
private:
	std::vector<D3DMATERIAL9> m_vecMaterial;
	std::map<std::string, cWoman*> m_vecWoman;
public:
	cAseLoader();
	~cAseLoader();
	void Load(OUT std::vector<cWoman*>& vecWoman, IN char* szFolder, IN char* szFile);
};

