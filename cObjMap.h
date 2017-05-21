#pragma once
#include "iMap.h"
class cObjMap :	public iMap
{
private:
	std::vector<D3DXVECTOR3> m_vecSurface;

public:
	cObjMap(IN char * szFolder, IN char * szFile, IN D3DXMATRIXA16 * pMat);
	~cObjMap(void);

	void LoadObjMap(IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat = NULL);
	void LoadRawMap(IN char* szFolder, IN char* szFile, IN D3DXMATRIXA16* pMat = NULL);

	virtual bool GetHeight(IN float x, OUT float & y, IN float z) override;
};

