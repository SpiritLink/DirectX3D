#pragma once

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;	
	/// 누적된 행렬의 정보를 가지고 있음
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<D3DMATERIAL9>		vecMtl;
	std::vector<LPDIRECT3DTEXTURE9> vecTexture;
	LPD3DXMESH		pOrigMesh;				/// 원본 메쉬
	D3DXMATRIX**	ppBoneMatrixPtrs;		/// 현재 메쉬에 영향을 주는 연관된 월드 매트릭스의 포인터
	D3DXMATRIX*		pBoneOffsetMatrices;	/// 로컬스페이스로 보내는 매트릭스 계산
	D3DXMATRIX*		pCurrentBoneMatrices;	/// 각 본에서 계산된 월드매트릭스 계산된것
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy();
	~cAllocateHierarchy();


protected:
	SYNTHESIZE(std::string, m_sFolder, Folder);
public:
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name,
		LPD3DXFRAME *ppNewFrame) override;

	STDMETHOD(CreateMeshContainer)(THIS_
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) override;

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) override;
};

