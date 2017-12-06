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
	for(int i = 0; i < TEAM_END - 1; ++i) m_characterTime[i] = GetTickCount();
	m_characterTime[NORTH] = 0;
	cout << "SceneManager is initialized!" << endl;
	m_sound = new Sound();
	int soundBG = m_sound->CreateSound("Dependencies//SoundSamples//MF-W-90.XM");
	m_sound->PlaySounds(soundBG, true, 0.2f);

}

void CSceneMgr::InitNorthTeam()
{
	
	// Left Building
	m_objects[NORTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(-BUILDING_LEFT_XPOS, NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(1.0f, 0.0f, 0.0f, 1.0f), LEVEL_SKY)));

	// Mid Building
	m_objects[NORTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(0.0f, NORTH_BUILDING_YPOS + 40.0f),
				BUILDING_SIZE, Color(1.0f, 0.0f, 0.0f, 1.0f), LEVEL_SKY)));

	// Right Building
	m_objects[NORTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::NORTH, OBJTYPE::OBJECT_BUILDING,
				Pos(BUILDING_LEFT_XPOS, NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(1.0f, 0.0f, 0.0f, 1.0f), LEVEL_SKY)));
}
void CSceneMgr::InitSouthTeam()
{

	// Left Building
	m_objects[SOUTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::SOUTH, OBJTYPE::OBJECT_BUILDING,
				Pos(-BUILDING_LEFT_XPOS, -NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(0.0f, 0.0f, 1.0f, 1.0f), LEVEL_SKY)));

	// Mid Building
	m_objects[SOUTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::SOUTH, OBJTYPE::OBJECT_BUILDING,
				Pos(0.0f, -(NORTH_BUILDING_YPOS + 40.0f)),
				BUILDING_SIZE, Color(0.0f, 0.0f, 1.0f, 1.0f), LEVEL_SKY)));

	// Right Building
	m_objects[SOUTH].emplace_back(
		FACTORYMANAGER->CreateObj(
			ObjectInfo(this->GetID(), OWNER::NONE, TEAMTYPE::SOUTH, OBJTYPE::OBJECT_BUILDING,
				Pos(BUILDING_LEFT_XPOS, -NORTH_BUILDING_YPOS),
				BUILDING_SIZE, Color(0.0f, 0.0f, 1.0f, 1.0f), LEVEL_SKY)));
}

void CSceneMgr::CheckCollision()
{
	for (int k = 0; k < TEAM_END; ++k) {
		for (auto& d : m_objects[k]) {
			for (int i = 0; i < m_objects[k].size(); ++i) {

				for (int j = 0; j < m_objects[(k + 1) % TEAM_END].size(); ++j) d->CheckCollision(m_objects[(k + 1) % TEAM_END][j]);
				
				if (d->GetObjType() == OBJECT_CHARACTER || d->GetObjType() == OBJECT_BUILDING) {
					for (auto& sd : m_shootObjects[(k + 1) % TEAM_END]) d->CheckCollision(sd);
					
				}
			}

		}
	}

}
void CSceneMgr::RemoveObject()
{
	for (int i = 0; i < TEAM_END; ++i) {
		{
			vector<shared_ptr<CObject>>::iterator itor = m_objects[i].begin();
			while (itor != m_objects[i].end()) {
				if ((*itor)->DoHavetoBeRemoved()) itor = m_objects[i].erase(itor);
				else ++itor;
			}
		}

		{
			vector<shared_ptr<CObject>>::iterator itor = m_shootObjects[i].begin();
			while (itor != m_shootObjects[i].end()) {
				if ((*itor)->DoHavetoBeRemoved()) itor = m_shootObjects[i].erase(itor);
				else ++itor;
			}
		}
	}
}

void CSceneMgr::CreateNorthCharacter()
{
	if (m_characterTime[NORTH] + NORTH_CHARACTER_TIME < GetTickCount()) {
		Pos pos(rand() % WINDOW_WIDTH / 4.0f, rand() % WINDOW_HEIGHT / 4.0f);

		if (rand() % 2 == 1) pos.x = -pos.x;

		ObjectInfo info(SCENEMANAGER->GetID(), OWNER::NONE,TEAMTYPE::NORTH, OBJTYPE::OBJECT_CHARACTER,
			pos, CHARACTER_SIZE, Color(1.0f, 0.0f, 0.0f, 1.0f), LEVEL_GROUND);
		SCENEMANAGER->AddNorthObject(FACTORYMANAGER->CreateObj(info));
		m_characterTime[NORTH] = GetTickCount();
	}
}

void CSceneMgr::Render()
{
	const char* name;

	for (int i = 0; i < TEAM_END; ++i) {
		if (i == 0) name = "NorthBuilding";
		else name = "SouthBuilding";
		for (auto& d : m_objects[i]) {
			if (d->GetObjType() == OBJECT_BUILDING) {
				m_renderer->DrawTexturedRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
					d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
					d->GetColor().a, IMAGEMANAGER->GetImage()[name], d->GetRenderLevel());

				m_renderer->DrawSolidRectGauge(d->GetPos().x, d->GetPos().y + d->GetSize() / 1.5f, d->GetPos().z,
					d->GetSize(), d->GetSize() / 10.0f, d->GetColor().r, d->GetColor().g, d->GetColor().b, d->GetColor().a, d->GetLifePercent(), LEVEL_GOD);

				m_renderer->DrawTexts(d->GetPos().x - d->GetSize() / 1.4f, d->GetPos().y + d->GetSize() / 1.5f, GLUT_STROKE_ROMAN, d->GetColor().r, d->GetColor().g, d->GetColor().b, "HP: ");
			}

			else {
				if (d->GetTeamType() == NORTH) name = "NC";
				else name = "SC";
				m_renderer->DrawTexturedRectSeq(d->GetPos().x, d->GetPos().y, d->GetPos().z,
					d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b, d->GetColor().a,
					IMAGEMANAGER->GetImage()[name], d->GetRow(), d->GetCol(), 8, 8, d->GetRenderLevel());


				m_renderer->DrawSolidRectGauge(d->GetPos().x, d->GetPos().y + d->GetSize(), d->GetPos().z,
					d->GetSize(), d->GetSize() / 5.0f, d->GetColor().r, d->GetColor().g, d->GetColor().b, d->GetColor().a, d->GetLifePercent(), LEVEL_GOD);


			}
			

		}

		for (auto& d : m_shootObjects[i]) {
			m_renderer->DrawSolidRect(d->GetPos().x, d->GetPos().y, d->GetPos().z,
				d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
				d->GetColor().a, d->GetRenderLevel());

			if (d->GetObjType() == OBJECT_BULLET) {
				m_renderer->DrawParticle(d->GetPos().x, d->GetPos().y, d->GetPos().z,
					d->GetSize(), d->GetColor().r, d->GetColor().g, d->GetColor().b,
					d->GetColor().a, d->GetDir().x, d->GetDir().y, IMAGEMANAGER->GetImage()["Fire"], 10000);
			}
		}
	}

	
	// Render BackGround
	m_renderer->DrawTexturedRect(0.0f, 0.0f, 0.0f,
		WINDOW_HEIGHT, 1.0f, 1.0f, 1.0f,
		0.2f, IMAGEMANAGER->GetImage()["BackGround"], LEVEL_UNDERGROUND);

	

}

void CSceneMgr::Update(float time)
{

	this->CheckCollision();
	this->CreateNorthCharacter();

	for (int i = 0; i < TEAM_END; ++i) {
		for (auto& d : m_objects[i]) d->Update(time);
		for (auto& d : m_shootObjects[i]) d->Update(time);

	}

	this->RemoveObject();

}