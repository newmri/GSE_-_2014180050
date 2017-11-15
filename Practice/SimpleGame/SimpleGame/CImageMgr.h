#pragma once

#include <map>

class CImageMgr
{
public:
	static CImageMgr* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new CImageMgr;
			m_instance->Init();
		}
		return m_instance;
	}

	void Init();

public:
	std::map<const char*, int>& GetImage() { return m_imageList; }

private:
	CImageMgr(void) {};
	~CImageMgr(void) { delete m_instance; };

	static CImageMgr* m_instance;

private:
	std::map<const char*, int> m_imageList;

};