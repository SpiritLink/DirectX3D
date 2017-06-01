#pragma once

class cCamera;
class cFrustum
{
public:
	cFrustum();
	~cFrustum();
private:
	std::vector<D3DXVECTOR3> m_vecProjVertex;
	std::vector<D3DXVECTOR3> m_vecWorldVertex;
	std::vector<D3DXPLANE> m_vecPlane;

	cCamera* m_pCam;

public:
	void Setup();
	void Update();
	bool IsIn(ST_SPHERE* pSphere);		/// 질럿이나 큐브맨의 위치 같은 개념이 필요 (수천개 뿌려서 확인)

};

