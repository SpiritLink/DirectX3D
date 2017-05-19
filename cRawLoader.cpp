
#include "stdafx.h"
#include "cRawLoader.h"

#define RAWSIZE 257
#define TILESIZE 256
cRawLoader::cRawLoader()
{
}

cRawLoader::~cRawLoader()
{
}

LPD3DXMESH cRawLoader::Load(IN char * szFolder, IN char * szFile)
{
	LPD3DXMESH pMesh = NULL;
	m_vecVertex.clear();
	m_vecIndex.clear();
	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "rb");

	unsigned int c;

	while (true)
	{
		if (feof(fp)) break;

		c = fgetc(fp);
		m_vecRaw.push_back(c);
	}
	m_vecRaw.pop_back();

	ST_PNT_VERTEX p;
	p.n = D3DXVECTOR3(0, 1, 0);	///���� ���� ����Ʈ��
	p.p = D3DXVECTOR3(0, 0, 0);	///x, y, z ���� �ٲ������
	p.t = D3DXVECTOR2(0, 0);	/// �ؽ��� 0 ���� 1������ ��

	for (int i = 0; i < RAWSIZE; ++i)
	{
		for (int j = 0; j < RAWSIZE; ++j)
		{
			p.p.x = j;
			//p.p.y = m_vecRaw[j + i * RAWSIZE] / (float)10.0f;
			p.p.y = 0.0f;

			p.p.z = i;

			if (j == 0)
				p.t.x = 0;
			else
				p.t.x = j / (float)RAWSIZE;

			if (i == 0)
				p.t.y = 0;
			else
				p.t.y = 1.0f - (i / (float)RAWSIZE);

			m_vecVertex.push_back(p);
		}
	}

	for (int i = 1; i < TILESIZE; ++i)
	{
		for (int j = 1; j < TILESIZE; ++j)
		{
			D3DXVECTOR3 vHorizon, vVertical, vn;
			vHorizon =  m_vecVertex[i + (j * RAWSIZE) + 1].p - m_vecVertex[i + (j * RAWSIZE) - 1].p;				///����
			vVertical = m_vecVertex[i + (j * RAWSIZE) - RAWSIZE].p - m_vecVertex[i + (j * RAWSIZE) + RAWSIZE].p;	///����
			D3DXVec3Normalize(&vHorizon, &vHorizon);	///���� ����ȭ
			D3DXVec3Normalize(&vVertical, &vVertical);	///���� ����ȭ
			D3DXVec3Cross(&vn, &vHorizon, &vVertical);	///����
			D3DXVec3Normalize(&vn, &vn);				///�������� ����ȭ
			m_vecVertex[i + j * RAWSIZE].n = vn;		///����
		}
	}

	for (int i = 0; i < TILESIZE; ++i)		///x
	{
		for (int j = 0; j < TILESIZE; ++j)	///y
		{
			WORD k;
			k = j + (i * RAWSIZE);					m_vecIndex.push_back(k);	///���� �Ʒ�
			k = j + (i * RAWSIZE) + RAWSIZE;		m_vecIndex.push_back(k);	///���� ��
			k = j + (i * RAWSIZE) + 1 + RAWSIZE;	m_vecIndex.push_back(k);	///������ ��

			k = j + i * RAWSIZE;					m_vecIndex.push_back(k);	///���� �Ʒ�
			k = j + (i * RAWSIZE) + 1 + RAWSIZE;	m_vecIndex.push_back(k);	///������ ��
			k = j + (i * RAWSIZE) + 1;				m_vecIndex.push_back(k);	///������ �Ʒ�
		}
	}

	m_vecAttribute.resize(m_vecIndex.size() / 3, (DWORD)0);
	//���⼭ �޽��� �ε����� �����͸� �� ���� �Ž�ä�� ��ȯ�� ������.
	D3DXCreateMeshFVF(m_vecIndex.size() / 3, m_vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDevice, &pMesh);

	ST_PNT_VERTEX* pv = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pv);
	memcpy_s(pv, m_vecVertex.size() * sizeof(ST_PNT_VERTEX), &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	WORD* index = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)&index);
	memcpy_s(index, m_vecIndex.size() * sizeof(WORD), &m_vecIndex[0], m_vecIndex.size() * sizeof(WORD));
	pMesh->UnlockIndexBuffer();

	DWORD* attribute = 0;
	pMesh->LockAttributeBuffer(0, &attribute);
	memcpy_s(attribute, m_vecAttribute.size() * sizeof(DWORD), &m_vecAttribute[0], m_vecAttribute.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	////optimize
	//std::vector<DWORD> adjacencyBuffer(pMesh->GetNumFaces() * 3);
	//pMesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	//pMesh->OptimizeInplace(
	//	D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
	//	&adjacencyBuffer[0], 0, 0, 0);

	return pMesh;

}