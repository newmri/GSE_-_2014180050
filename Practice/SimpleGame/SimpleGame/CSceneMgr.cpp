#include "stdafx.h"
#include "Objects.h"

void CSceneMgr::Init()
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
		Pos pos;

		pos.x = static_cast<float>(rand() % (WINDOW_WIDTH / 2));
		if (rand() % 2) pos.x = -pos.x;
		pos.y = static_cast<float>(rand() % (WINDOW_HEIGHT / 2));
		if (rand() % 2) pos.y = -pos.y;
		m_objects.emplace_back(FACTORYMANAGER->CreateObj(OBJTYPE::OBJECT, pos, 4,
			Color(1.0f, 1.0f, 1.0f, 1.0f)));
	}

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
		for (auto& d : m_objects) d->SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
		m_time = GetTickCount();
	}

}