#pragma once

#include <atlstr.h>
#include <map>

class CImageMgr
{
public:
	static CImageMgr* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CImageMgr;

		return m_instance;
	}


private:
	CImageMgr(void) {};
	~CImageMgr(void) { delete m_instance; };

	static CImageMgr* m_instance;
	std::map<CString, int>& GetImage();

};