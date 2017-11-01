#include "stdafx.h"
#include "Objects.h"

void CSceneMgr::Init()
{
	ObjectInfo info(OBJTYPE::OBJECT_BUILDING, Pos(), 100, Color(1.0f, 1.0f, 1.0f, 1.0f));
	m_objects.emplace_back(FACTORYMANAGER->CreateObj(info));

	m_time = GetTickCount();
}

void CSceneMgr::CheckCollision()
{
	for (auto& d : m_objects) {
		for (int i = 0; i < m_objects.size(); ++i) {
			if (d != m_objects[i]) d->CheckCollision(m_objects[i]);
		}
	}
}
void CSceneMgr::RemoveObject()
{
	vector<shared_ptr<CObject>>::iterator itor = m_objects.begin();
	while (itor != m_objects.end()) {
		if ((*itor)->DoHavetoBeRemoved()) itor = m_objects.erase(itor);
		else ++itor;
	}
}

void CSceneMgr::Update(float time)
{

	this->CheckCollision();
	for (auto& d : m_objects) d->Update(time);
	this->RemoveObject();
	if (m_time + COLOR_ROLL_BACK_TIME < GetTickCount()) {
		for (auto& d : m_objects) d->RollBackColor();
		m_time = GetTickCount();
	}

}