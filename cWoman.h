#pragma once
#include "cCharacter.h"
class cFrame;

class cWoman : public cCharacter
{
protected:
	cFrame*			m_pRootFrame;
	cFrame*			m_pStandFrame;
public:
	cWoman();
	~cWoman();
	void Setup();
	void update();
	void Render();
	cFrame* getRootFrame() { return m_pRootFrame; }
};

