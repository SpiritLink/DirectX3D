#include "stdafx.h"
#include "cWoman.h"
#include "cFrame.h"
#include "cAseLoader.h"
cWoman::cWoman()
	: m_pRootFrame(NULL),
	m_pStandFrame(NULL)
{
}


cWoman::~cWoman()
{
	m_pRootFrame->Destroy();
	SAFE_DELETE(m_pRootFrame);
	m_pStandFrame->Destroy();
	SAFE_DELETE(m_pStandFrame);
}

void cWoman::Setup()
{
	cCharacter::Setup(NULL,0);

	cAseLoader loadAse;
	m_pRootFrame = loadAse.Load("woman/woman_01_all.ASE");
	m_pRootFrame->SetPosition(&m_vPosition);
	cAseLoader loadAse2;
	m_pStandFrame = loadAse2.Load("woman/woman_01_all_stand.ASE");
	m_pStandFrame->SetPosition(&m_vPosition);
}

void cWoman::update()
{
	cCharacter::Update(NULL);
	if (m_pRootFrame)
	{
		if (GetKeyState('W') & 0x8000)
		{
			m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), &m_matWorld);
		}

		if (!(GetKeyState('W') & 0x8000))
		{
			m_pStandFrame->Update(m_pStandFrame->GetKeyFrame(), &m_matWorld);
		}
	}
}

void cWoman::Render()
{
	for (int i = 0; i < 1000; ++i)
	{
		if (m_pRootFrame)
		{
			if (GetKeyState('W') & 0x8000)
			{
				m_pRootFrame->Render();
			}
			if (!(GetKeyState('W') & 0x8000))
			{
				m_pStandFrame->Render();
			}
		}
	}
}
