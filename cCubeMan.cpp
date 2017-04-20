#include "stdafx.h"
#include "cCubeMan.h"

#include "cHead.h"
#include "cBody.h"
#include "cLeftArm.h"
#include "cLeftLeg.h"
#include "cRightArm.h"
#include "cRightLeg.h"

cCubeMan::cCubeMan()
	: m_pRoot(NULL)
{
}


cCubeMan::~cCubeMan()
{
	m_pRoot->Destroy();
	SAFE_DELETE(m_pRoot);
}

void cCubeMan::Setup()
{
	m_pRoot = new cCubeNode;
	cCubeNode* head = new cHead;
	cCubeNode* body = new cBody;
	cCubeNode* leftArm = new cLeftArm;
	cCubeNode* leftLeg = new cLeftLeg;
	cCubeNode* rightArm = new cRightArm;
	cCubeNode* rightLeg = new cRightLeg;

	head->Setup();
	body->Setup();
	leftArm->Setup();
	leftLeg->Setup();
	rightArm->Setup();
	rightLeg->Setup();

	m_pRoot->AddChild(head);
	m_pRoot->AddChild(body);
	m_pRoot->AddChild(leftArm);
	m_pRoot->AddChild(rightArm);
	m_pRoot->AddChild(leftLeg);
	m_pRoot->AddChild(rightLeg);

	m_pRoot->Setup();
}

void cCubeMan::Update()
{
	m_pRoot->Update();
}

void cCubeMan::Render()
{
	m_pRoot->Render();
}
