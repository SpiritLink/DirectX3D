#pragma once
class cGrid;
class cGroup;
class cCharacter
{
public:
	cCharacter();

protected:
	float			m_fRotY;
	float			m_pU;
	float			m_pV;
	float			m_pDist;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;

	D3DXVECTOR3		m_vRayPosition;
	D3DXVECTOR3		m_vRayDirection;
	std::vector<cGroup*>* m_pVecGroup;

	bool			m_bIsIdle;
	void moveCheck();
public:
	virtual ~cCharacter();

	virtual void Setup(std::vector<ST_PC_VERTEX>* vecVertex, int nType);
	virtual void Update();
	virtual void Render();

	virtual D3DXVECTOR3 & GetPosition();
	void SetGroup(std::vector<cGroup*>* vecGroup) { m_pVecGroup = vecGroup; }
};

