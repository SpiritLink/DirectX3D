#pragma once
class cRawLoader
{
private:
	std::vector<ST_PNT_VERTEX>    m_vecVertex;
	std::vector<unsigned int>    m_vecRaw;
	std::vector<DWORD>            m_vecAttribute;
	std::vector<WORD>            m_vecIndex;
public:
	cRawLoader();
	~cRawLoader();

	LPD3DXMESH Load(IN char* szFolder, IN char* szFile);
	std::vector<unsigned int> LoadRawData(IN char* szFolder, IN char* szFile);
	void LoadSurface(OUT std::vector<D3DXVECTOR3>& vecSurface,IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat);

};