#pragma once

class iMap;

class cCharacter
{
public:
	cCharacter();

protected:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

	D3DXVECTOR3		m_vDestination;
	iMap*			m_pMap;
public:
	virtual ~cCharacter();

	virtual void Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType);
	virtual void Update(iMap* pMap);	//	<< :
	virtual void Render();

	virtual D3DXVECTOR3 & GetPosition();
	void SetDestination(D3DXVECTOR3 vDestination);
};

