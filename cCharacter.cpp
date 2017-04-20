#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter()
	: m_vDirection(0,0,1), m_vPosition(0,0,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
	//
}

void cCharacter::Update()
{
	// : to do something
}

void cCharacter::Render()
{
}

D3DXVECTOR3 & cCharacter::GetPosition()
{
	return m_vPosition;
}
