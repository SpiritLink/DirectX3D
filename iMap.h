#pragma once
class iMap
{
public:
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) = 0;	//���� �����Լ� ����
	
	// >> :
	virtual void Render() = 0;
	// << :
};

