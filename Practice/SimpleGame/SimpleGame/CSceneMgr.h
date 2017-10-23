#pragma once

#include "Define.h"

class CSceneMgr
{
public:
	CSceneMgr() { this->Init(); }
public:
	void Init();
	void AddObject(shared_ptr<CObject> obj) { m_objects.emplace_back(obj); }
	void Update();

public:
	const vector<shared_ptr<CObject>> GetObjects() { return m_objects; }
private:
	vector<shared_ptr<CObject>> m_objects;
	DWORD m_time;
};