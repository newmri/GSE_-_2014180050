#include "stdafx.h"
#include "Define.h"
#include "Objects.h"

CSceneMgr* CSceneMgr::m_instance = nullptr;

void CSceneMgr::Init()
{
	m_id = 0;
	this->InitNorthTeam();
	this->InitSouthTeam();
	m_time = GetTickCount();

	cout << "SceneManager is initialized!" << endl;
	
}

void CSceneMgr::InitNorthTeam()
{
	
	// Left Building
	m_objects[NORTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(-BUILDING_LEFT_XPOS, NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f))));

	// Mid Building
	m_objects[NORTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(0.0f, NORTH_BUILDING_YPOS + 40.0f),
				BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f))));

	// Right Building
	m_objects[NORTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(BUILDING_LEFT_XPOS, NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f))));
}
void CSceneMgr::InitSouthTeam()
{

	// Left Building
	m_objects[SOUTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(-BUILDING_LEFT_XPOS, -NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f))));

	// Mid Building
	m_objects[SOUTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(0.0f, -(NORTH_BUILDING_YPOS + 40.0f)),
				BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f))));

	// Right Building
	m_objects[SOUTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(BUILDING_LEFT_XPOS, -NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(1.0f, 1.0f, 0.0f, 1.0f))));
}

void CSceneMgr::CheckCollision()
{
	for (auto& d : m_objects[NORTH]) {
		for (int i = 0; i < m_objects[NORTH].size(); ++i) {
			if (d != m_objects[NORTH][i]) d->CheckCollision(m_objects[NORTH][i]);
			if (d->GetObjType() == OBJECT_CHARACTER || d->GetObjType() == OBJECT_BUILDING) {
				for (auto& sd : m_shootObjects[NORTH]) {
					if(sd->GetOwnerID() != d->GetID()) d->CheckCollision(sd);
				}

			}
		}

	}
	
}
void CSceneMgr::RemoveObject()
{
	{
		vector<shared_ptr<CObject>>::iterator itor = m_objects[NORTH].begin();
		while (itor != m_objects[NORTH].end()) {
			if ((*itor)->DoHavetoBeRemoved()) itor = m_objects[NORTH].erase(itor);
			else ++itor;
		}
	}

	{
		vector<shared_ptr<CObject>>::iterator itor = m_shootObjects[NORTH].begin();
		while (itor != m_shootObjects[NORTH].end()) {
			if ((*itor)->DoHavetoBeRemoved()) itor = m_shootObjects[NORTH].erase(itor);
			else ++itor;
		}
	}
}

void CSceneMgr::Render()
{
	for (int i = 0; i < 2; ++i) {
		for (auto& d : m_objects[i]) {
			if (d->GetObjType() == OBJECT_BUILDING)
				m_renderer->DrawTexturedRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
					d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
					d->GetColor().a, IMAGEMANAGER->GetImage()["NorthBuilding"]);

			else
				m_renderer->DrawSolidRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
					d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
					d->GetColor().a);
		}

		for (auto& d : m_shootObjects[i]) {
			m_renderer->DrawSolidRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
				d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
				d->GetColor().a);
		}
	}
}

void CSceneMgr::Update(float time)
{

	this->CheckCollision();
	for (int i = 0; i < 2; ++i) {
		for (auto& d : m_objects[i]) d->Update(time);
		for (auto& d : m_shootObjects[i]) d->Update(time);

		if (m_time + COLOR_ROLL_BACK_TIME < GetTickCount()) {
			for (auto& d : m_objects[i]) d->RollBackColor();
			m_time = GetTickCount();
		}
	}

	this->RemoveObject();

}