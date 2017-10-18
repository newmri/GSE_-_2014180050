#pragma once

#include "Define.h"

class CSceneMgr
{
public:
	CSceneMgr() { this->Init(); }
public:
	void Init();
	void Update();

	const vector<shared_ptr<CObject>> GetObjects() { return m_objects; }
private:
	vector<shared_ptr<CObject>> m_objects;
};