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
			Color(1.0f, 1.0f, 1.0f, 1)));
	}
}

void CSceneMgr::Update()
{
	for (auto& d : m_objects) {
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) {
			if(d != m_objects[i]) d->CheckCollision(m_objects[i]);
		}
	}
	for (auto& d : m_objects) d->Update();
}