#include "stdafx.h"
#include "Define.h"
#include "Objects.h"

CSceneMgr* CSceneMgr::m_instance = nullptr;

void CSceneMgr::Init()
{
	m_id = 0;
	ObjectInfo info(this->GetID(), OWNER::NONE, OBJTYPE::OBJECT_BUILDING, Pos(), BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f));
	m_objects.emplace_back(FACTORYMANAGER->CreateObj(info));

	m_time = GetTickCount();

	cout << "SceneManager is initialized!" << endl;
	
	m_buildingId = m_renderer->CreatePngTexture("Resources\\Building.png");
}

void CSceneMgr::CheckCollision()
{
	for (auto& d : m_objects) {
		for (int i = 0; i < m_objects.size(); ++i) {
			if (d != m_objects[i]) d->CheckCollision(m_objects[i]);
			if (d->GetObjType() == OBJECT_CHARACTER || d->GetObjType() == OBJECT_BUILDING) {
				for (auto& sd : m_shootObjects) {
					if(sd->GetOwnerID() != d->GetID()) d->CheckCollision(sd);
				}

			}
		}

	}
	
}
void CSceneMgr::RemoveObject()
{
	{
		vector<shared_ptr<CObject>>::iterator itor = m_objects.begin();
		while (itor != m_objects.end()) {
			if ((*itor)->DoHavetoBeRemoved()) itor = m_objects.erase(itor);
			else ++itor;
		}
	}

	{
		vector<shared_ptr<CObject>>::iterator itor = m_shootObjects.begin();
		while (itor != m_shootObjects.end()) {
			if ((*itor)->DoHavetoBeRemoved()) itor = m_shootObjects.erase(itor);
			else ++itor;
		}
	}
}

void CSceneMgr::Render()
{
	for (auto& d : m_objects) {
		m_renderer->DrawTexturedRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
			d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
			d->GetColor().a, m_buildingId);
	}

	for (auto& d : m_shootObjects) {
		m_renderer->DrawSolidRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
			d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
			d->GetColor().a);
	}
}
void CSceneMgr::Update(float time)
{

	this->CheckCollision();
	for (auto& d : m_objects) d->Update(time);
	for (auto& d : m_shootObjects) d->Update(time);
	this->RemoveObject();
	if (m_time + COLOR_ROLL_BACK_TIME < GetTickCount()) {
		for (auto& d : m_objects) d->RollBackColor();
		m_time = GetTickCount();
	}

}