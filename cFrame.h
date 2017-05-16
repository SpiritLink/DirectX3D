#pragma once
#include "cObject.h"
#include "cMtlTex.h"
class cFrame :
	public cObject
{
public:
	cFrame();
	~cFrame();
private:
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matLocalTM, LocalTM);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorldTM, WorldTM);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	SYNTHESIZE_PASS_BY_REF(std::vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack);
	SYNTHESIZE_ADD_REF(cMtlTex*, m_pMtlTex, MtlTex);
	D3DXVECTOR3*	m_pPosition;
	std::vector<cFrame*> m_vecChild;
	int						m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;

	LPD3DXMESH m_pMesh;
public:
	void Update(int nKeyFrame, D3DXMATRIXA16* pMatParent);
	void Render();
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalcOriginalLocalTM(D3DXMATRIXA16 * pMatParent);

	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwFrameSpeed;
	DWORD	m_dwTicksPerFrame;
	DWORD	m_dwStartTick;
	DWORD	m_dwKeyPressTick;
	int		GetKeyFrame();
	int		GetMiddleKeyFrame() { return (m_dwFirstFrame + m_dwLastFrame) / 2; }
	void	SetKeyPressTick(DWORD value) { m_dwKeyPressTick = value; }
	void	CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void	CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matR);
	void	SetPosition(D3DXVECTOR3* m_vPosition) { m_pPosition = m_vPosition; }

	void BuildVertexBuffer(std::vector<ST_PNT_VERTEX>& vertex);
	LPD3DXMESH* getMesh() { return &m_pMesh; }
};

