#pragma once

#define g_pObjectManager cObjectManager::GetInstance() //

class cObjectManager
{
//public:
//	cObjectManager();
//	~cObjectManager();
// >> :
private:
	SINGLETONE(cObjectManager);
	
	std::set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject)
	{
		m_setObject.insert(pObject);
	}

	void RemoveObject(cObject* pObject)
	{
		m_setObject.erase(pObject);
	}

	void Destroy()
	{
		m_setObject.clear();	//SAFE_RELEASE한다고 해서 메모리 자체를 날리는게 아니기 때문
	}
// << :
};

