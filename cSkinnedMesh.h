#pragma once
class cSkinnedMesh
{
public:
	cSkinnedMesh();
	~cSkinnedMesh();

protected:
	LPD3DXFRAME m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;

	// >> :
	float m_fBlendTime;
	float m_fPassedBlendTime;
	bool m_isAnimBlend;
	// << :
public:
	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);

	void SetAnimationIndexBlend(int nIndex);
	/*
	이 함수를 구현해 와야 한다.
	m_pAnimController->GetNumAnimationSets(); 현재 설정된 애니메이션의 개수를 알 수 있음
	LPD3DXANIMATIONSET ...
	m_pAnimController->GetAnimationSet(index, ....) 정보를 얻어올 수 있는 구조체가 한개 들어가게 됨
	m_pAnimController->SetTrackAnimationSet(0, ....)
	주트랙이 0번이기 때문에 첫번째 인자는 0이다.
	마우스 우클릭 할때마다 애니메이션의 내용이 변경되게 만들어보자
	*/
};

