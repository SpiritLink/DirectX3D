#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"

cSkinnedMesh::cSkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.3f)		/// �ΰ��� �ִϸ��̼��� 0.3�ʿ� ���ļ� �÷��� ��Ų��.
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)		/// �������� �ǰ� �ִ��� �ƴ����� ����
{
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimController);
}

void cSkinnedMesh::Setup(char* szFolder, char* szFile)
{
	std::string sFullPath(szFolder);
	sFullPath = sFullPath + std::string("/") + std::string(szFile);

	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);

	/// ������ �� �ִ°� �ε���
	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimController);///�ִϸ��̼ǿ� ���� ��� ������ Controller�� ���ۤ�

	SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Update()
{
	// >> :
	if (m_isAnimBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();
		if (m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;	///0.3�ʰ� ������ ���̻� �������� �ʰڴ�.
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackWeight(1, false);	/// 1��Ʈ���� ���̻� ������� �ʰڴ�.
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);			/// ����ġ�� ����Ǹ鼭 ���� �ȴ�.
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
	// << : ����ġ�� ���õ� �κ�

	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	///����(�θ�)�� Matrix�� ������
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	if (pParent)
	{
		pBone->CombinedTransformationMatrix *=
			((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); ++i)
			{
				g_pD3DDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh =
			(ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone =
					(ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] =
					&(pBone->CombinedTransformationMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh =
			(ST_BONE_MESH*)pFrame->pMeshContainer;

		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}

	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}
void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int nCnt = nIndex;
	int nAniNum = m_pAnimController->GetNumAnimationSets();
	if (nIndex >= nAniNum) nCnt = nCnt % nAniNum;

	LPD3DXANIMATIONSET pAnimSet;
	m_pAnimController->GetAnimationSet(nCnt, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0,pAnimSet);

	// ����
	m_pAnimController->GetPriorityBlend();

	SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	m_isAnimBlend = true;
	m_fPassedBlendTime = 0.0f;

	int nAniNum = m_pAnimController->GetNumAnimationSets();
	if (nIndex >= nAniNum) nIndex = nIndex % nAniNum;

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);			/// 0��Ʈ���� ���� �����س��� [���� �÷�������]
	
	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);	/// ���� �ִϸ��̼��� ������ ���´�.
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f);				/// �ִϸ��̼��� ù��°���� ����Ѵ�.

	m_pAnimController->SetTrackWeight(0, 0.0f);					/// ����ġ (0��Ʈ���� �ִ°� ����ġ�� ���� ���� õõ�� �þ��)
	m_pAnimController->SetTrackWeight(1, 1.0f);					/// 1.0���� �����Ѵ�.

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);


}