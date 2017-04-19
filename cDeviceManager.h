#pragma once
#define g_pDeviceManager	cDeviceManager::GetInstance()
#define g_pD3DDevice		cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
public:
	//	cDeviceManager();
	//	~cDeviceManager();
	//public:
	//	/*
	//	GetInstance를 생성하면 있으면 가져오고 없으면 생성함
	//	static이라 메모리 할당할 필요 없음
	//	*/
	//	static cDeviceManager* GetInstance()
	//	{
	//		static cDeviceManager instance;
	//		return &instance;
	//	}
	SINGLETONE(cDeviceManager);
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	LPDIRECT3DDEVICE9 GetDevice();
	void Destroy();

};

