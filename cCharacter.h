#pragma once
class cGrid;

class cCharacter
{
public:
	cCharacter();

protected:
	float			m_fRotY;
	D3DXVECTOR3		m_vDirection;
	D3DXVECTOR3		m_vPosition;
	D3DXMATRIXA16	m_matWorld;
	bool			m_pIsIdle;
	
public:
	virtual ~cCharacter();

	virtual void Setup(std::vector<ST_PC_VERTEX>* vecVertex);
	virtual void Update();
	virtual void Render();

	virtual D3DXVECTOR3 & GetPosition();
};

