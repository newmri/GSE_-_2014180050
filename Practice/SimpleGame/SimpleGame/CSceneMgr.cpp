#include "stdafx.h"
#include "Objects.h"

void CSceneMgr::Init()
{
	ObjectInfo info(OBJTYPE::OBJECT_BUILDING, Pos(), BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f));
	m_objects.emplace_back(FACTORYMANAGER->CreateObj(info));

	m_time = GetTickCount();

	cout << "SceneManager is initialized!" << endl;
	
}

void CSceneMgr::CheckCollision()
{
	for (auto& d : m_objects) {
		for (int i = 0; i < m_objects.size(); ++i) {
			if (d != m_objects[i]) d->CheckCollision(m_objects[i]);
			if (d->GetObjType() == OBJECT_CHARACTER) {
				for (auto& d2 : m_objects) {
					if (d2->GetObjType() == OBJECT_BUILDING) {
						for (auto& bd : d2->GetBullet()) {
							d->CheckCollision(bd);
						}
					}
				}
			}
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

void CSceneMgr::Render()
{
	for (auto& d : m_objects) {
		m_renderer->DrawSolidRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
			d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
			d->GetColor().a);

		if (d->GetObjType() == OBJECT_BUILDING) {
			for (auto& d : d->GetBullet()) {
				m_renderer->DrawSolidRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
					d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
					d->GetColor().a);
			}
		}
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