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
	//	GetInstance�� �����ϸ� ������ �������� ������ ������
	//	static�̶� �޸� �Ҵ��� �ʿ� ����
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

