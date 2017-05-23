#pragma once
class iMap
{
public:
	virtual ~iMap() = 0;
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) = 0;	//순수 가상함수 선언
	
	// >> :
	virtual void Render() = 0;
	// << :
};

