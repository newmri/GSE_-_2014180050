#pragma once

#include <memory>
#include "Enum.h"

class CObject;
struct Pos;
struct Color;
struct ObjectInfo;

class CFactory
{
public:
	static CFactory* GetInstance()
	{
		if (m_instance == nullptr)
			m_instance = new CFactory;

		return m_instance;
	}

	std::shared_ptr<CObject> CreateObj(ObjectInfo objinfo);

private:
	CFactory(void) {};
	~CFactory(void) { delete m_instance; };

	static CFactory* m_instance;

};