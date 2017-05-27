#include "stdafx.h"
#include "cAllocateHierarchy.h"


cAllocateHierarchy::cAllocateHierarchy()
{
}


cAllocateHierarchy::~cAllocateHierarchy()
{
}

// : 새 프레임.. 뼈를 만들어 주는 함수.
STDMETHODIMP cAllocateHierarchy::CreateFrame(THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame)
{
	ST_BONE* pBone = new ST_BONE;

	ZeroMemory(pBone, sizeof(ST_BONE));

	// 이름을 복사 (무기를 붙이거나 뗄떼 이름으로 찾기 때문에 중요하다)
	if (Name)
	{
		pBone->Name = new char[strlen(Name) + 1];

		UINT length = lstrlen(Name) + 1;
		
		strcpy_s(pBone->Name, length * sizeof(TCHAR),
			Name);
	}

	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);

	*ppNewFrame = pBone;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer(
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;

	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));

	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		pBoneMesh->vecMtl.push_back(pMaterials[i].MatD3D);
		std::string sFullPath = m_sFolder;
		sFullPath = sFullPath + std::string("/") + std::string(pMaterials[i].pTextureFilename);
		pBoneMesh->vecTexture.push_back(g_pTextureManager->GetTexture(sFullPath));
	}

	pSkinInfo->AddRef();
	pBoneMesh->pSkinInfo = pSkinInfo;

	pMeshData->pMesh->AddRef();
	pBoneMesh->MeshData.pMesh = pMeshData->pMesh;
	pMeshData->pMesh->CloneMeshFVF(
		pMeshData->pMesh->GetOptions(),
		pMeshData->pMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pOrigMesh);
	/// 원본 메쉬에서 복사함 (Clone)

	DWORD dwNumBones = pSkinInfo->GetNumBones();
	pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
	pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
	pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];
	/// 각각의 얻어진걸 이용해 매트릭스와 연결된것들을 다시 설정한다.

	for (DWORD i = 0; i < dwNumBones; ++i)
	{
		pBoneMesh->pBoneOffsetMatrices[i] =
			*(pSkinInfo->GetBoneOffsetMatrix(i));
	}
	/// 전부 동적할당 되있기 때문에 정보를 얻어 다시 저장한다.

	*ppNewMeshContainer = pBoneMesh;

	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	/// 코드 삭제해주는 부분
	ST_BONE* pBone = (ST_BONE*)pFrameToFree;

	SAFE_DELETE_ARRAY(pBone->Name);

	SAFE_DELETE(pFrameToFree);
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;

	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	SAFE_RELEASE(pBoneMesh->MeshData.pMesh);
	SAFE_RELEASE(pBoneMesh->pOrigMesh);

	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE(pBoneMesh);
	return S_OK;
}
