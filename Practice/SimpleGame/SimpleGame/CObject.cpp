#include "stdafx.h"
#include "Objects.h"
#include "Define.h"

void CObject::Init(const ObjectInfo objInfo)
{
	m_objInfo = objInfo;
	m_backUpColor = objInfo.color;
	m_lifeTime = LIFE_TIME;

	float speed{};
	switch (m_objInfo.objType) {
	case OBJTYPE::OBJECT_BUILDING:
		m_objInfo.life = BUILDING_LIFE;
		m_objInfo.maxLife = m_objInfo.life;
		m_bulletSpawnTime = GetTickCount();
		speed = BUILDING_SPEED;
		break;
	case OBJTYPE::OBJECT_CHARACTER: 
		m_objInfo.life = CHARACTER_LIFE;
		m_objInfo.maxLife = m_objInfo.life;
		speed = CHARACTER_SPEED;
		break;
	case OBJTYPE::OBJECT_BULLET: 
		m_objInfo.life = BULLET_LIFE; 
		m_objInfo.maxLife = m_objInfo.life;
		speed = BULLET_SPEED; 
		break;
	case OBJTYPE::OBJECT_ARROW: 
		m_objInfo.life = ARROW_LIFE; 
		m_objInfo.maxLife = m_objInfo.life;
		m_arrowSpawnTime = GetTickCount();
		speed = ARROW_SPEED; 
		break;
	default: break;

	}
	switch (rand() % 8) {
	case 0: m_vPos.x = speed; m_dir.x = 1.0f; m_dir.y = 0.0f; m_col = R; m_row = 0; break;
	case 1: m_vPos.x = -speed; m_dir.x = -1.0f; m_dir.y = 0.0f; m_col = L; m_row = 0; break;
	case 2: m_vPos.y = speed; m_dir.y = 1.0f;  m_dir.x = 0.0f; m_col = U; m_row = 0; break;
	case 3: m_vPos.y = -speed; m_dir.y = -1.0f; m_dir.x = 0.0f; m_col = D; m_row = 0; break;
	case 4: m_vPos.x = speed; m_vPos.y = speed; m_dir.x = 1.0f; m_dir.y = 1.0f;  m_col = RU; m_row = 0; break;
	case 5: m_vPos.x = speed; m_vPos.y = -speed; m_dir.x = 1.0f; m_dir.y = -1.0f; m_col = RD; m_row = 0; break;
	case 6: m_vPos.x = -speed; m_vPos.y = speed; m_dir.x = -1.0f; m_dir.y = 1.0f; m_col = LU; m_row = 0; break;
	case 7: m_vPos.x = -speed; m_vPos.y = -speed; m_dir.x = -1.0f; m_dir.y = -1.0f; m_col = LD; m_row = 0; break;
	}
}

void CObject::CheckCollision(shared_ptr<CObject> other)
{
	if (((m_objInfo.pos.x + (m_objInfo.size / 2.0f)) > (other->GetPos().x - (other->GetSize() / 2.0f))) && // Right
		((m_objInfo.pos.x - (m_objInfo.size / 2.0f)) < (other->GetPos().x + (other->GetSize() / 2.0f))) && // Left
		((m_objInfo.pos.y + (m_objInfo.size / 2.0f)) > (other->GetPos().y - (other->GetSize() / 2.0f))) && // Top
		((m_objInfo.pos.y - (m_objInfo.size / 2.0f)) < (other->GetPos().y + (other->GetSize() / 2.0f)))) { // Bottom

		if (m_objInfo.objType == OBJTYPE::OBJECT_BUILDING){
			this->GotDamage(other->GetLife());
			other->SetDie();
			return;
		}

		if (m_objInfo.objType == OBJTYPE::OBJECT_CHARACTER &&
			other->GetObjType() == OBJTYPE::OBJECT_CHARACTER) {
			this->SetDie();
			other->SetDie();
		}
		switch(other->GetObjType()){
		case OBJTYPE::OBJECT_BUILDING:
			other->GotDamage(m_objInfo.life);
			this->SetDie();
			break;
		case OBJTYPE::OBJECT_BULLET:
			this->GotDamage(other->GetLife());
			other->SetDie();
			break;
		case OBJTYPE::OBJECT_ARROW:
			this->GotDamage(other->GetLife());
			other->SetDie();
			break;
		default: break;
		}

	}

}

void CObject::Move()
{
	if ((m_objInfo.pos.x + (m_objInfo.size / 2.0f) >= WINDOW_WIDTH / 2.0f) || // End of Right
		((m_objInfo.pos.x - (m_objInfo.size / 2) <= WINDOW_WIDTH / 2.0 * -1.0f))) { // End of Left
		if (m_objInfo.pos.x > 0.0f) m_objInfo.pos.x = (WINDOW_WIDTH / 2.0f) - (m_objInfo.size / 2.0f);
		else  m_objInfo.pos.x = -(WINDOW_WIDTH / 2.0f) + (m_objInfo.size / 2.0f);
		m_vPos.x = -m_vPos.x;
	}
	if ((m_objInfo.pos.y + (m_objInfo.size / 2.0f) >= WINDOW_HEIGHT / 2.0f) || // End of Top
		((m_objInfo.pos.y - (m_objInfo.size / 2.0f) <= WINDOW_HEIGHT / 2.0 * -1.0f))) { // End of Bottom
		if (m_objInfo.pos.y > 0.0f) m_objInfo.pos.y = (WINDOW_HEIGHT / 2.0f) - (m_objInfo.size / 2.0f);
		else  m_objInfo.pos.y = -(WINDOW_HEIGHT / 2.0f) + (m_objInfo.size / 2.0f);
		m_vPos.y = -m_vPos.y;
	}
	m_objInfo.pos = m_objInfo.pos + m_vPos * (m_time / 1000.0f);


	int n = m_vPos.x + m_vPos.y;
	if (m_objInfo.objType == OBJTYPE::OBJECT_CHARACTER) {
		switch (n) {
		case 0: 
			if (m_vPos.x > 0) { m_col = RD; m_dir.x = 1.0f, m_dir.y = -1.0f; break; } m_col = LU; m_dir.x = -1.0f, m_dir.y = 1.0f; break;
		case 300: if (m_vPos.x > 0) { m_col = R; m_dir.x = 1.0f; m_dir.y = 0.0f; break; }  m_col = U; m_dir.x = 0.0f; m_dir.y = 1.0f; break;
		case -300: if (m_vPos.x < 0) { m_col = L; m_dir.x = -1.0f; m_dir.y = 0.0f; break; } m_col = D; m_dir.x = 0.0f; m_dir.y = -1.0f; break;
		case 600: m_col = RU; m_dir.x = 1.0f; m_dir.y = 1.0f; break;
		case -600: m_col = LD; m_dir.x = -1.0f; m_dir.y = -1.0f; break;
		}
		m_row = (m_row + 1) % 8;
	}

	if (m_objInfo.objType == OBJTYPE::OBJECT_BULLET) {
		switch (n) {
		case 0:
			if (m_vPos.x > 0) { m_dir.x = -1.0f, m_dir.y = 1.0f; break; } m_dir.x = 1.0f, m_dir.y = -1.0f; break;
		case 600: if (m_vPos.x > 0) {  m_dir.x = -1.0f; m_dir.y = 0.0f; break; } m_dir.x = 0.0f; m_dir.y = -1.0f; break;
		case -600: if (m_vPos.x < 0) {  m_dir.x = 1.0f; m_dir.y = 0.0f; break; }  m_dir.x = 0.0f; m_dir.y = 1.0f; break;
		case 1200: m_dir.x = -1.0f; m_dir.y = -1.0f; break;
		case -1200:  m_dir.x = 1.0f; m_dir.y = 1.0f; break;
		}
	}
}

void CObject::SpawnBullet()
{
	if (m_bulletSpawnTime + BULLET_SPAWN_TIME < GetTickCount()) {
		ObjectInfo objInfo(SCENEMANAGER->GetID(), m_objInfo.id, m_objInfo.teamType, OBJTYPE::OBJECT_BULLET,
				           m_objInfo.pos, BULLET_SIZE, m_objInfo.color, LEVEL_UNDERGROUND);
		if (m_objInfo.teamType == TEAMTYPE::NORTH) SCENEMANAGER->AddNorthShootObjects(objInfo);
		else SCENEMANAGER->AddSouthShootObjects(objInfo);
		

		m_bulletSpawnTime = GetTickCount();
	}

}

void CObject::SpawnArrow()
{
	Color color;
	if (m_objInfo.teamType == NORTH) color = {0.5f, 0.2f, 0.7f, 1.0f };
	else color = { 1.0f, 1.0f, 0.0f, 1.0f };
	if (m_arrowSpawnTime + ARROW_SPAWN_TIME < GetTickCount()) {
		ObjectInfo objInfo(SCENEMANAGER->GetID(), m_objInfo.id, m_objInfo.teamType, OBJTYPE::OBJECT_ARROW,
						   m_objInfo.pos, ARROW_SIZE, color, LEVEL_UNDERGROUND);

		if (m_objInfo.teamType == TEAMTYPE::NORTH) SCENEMANAGER->AddNorthShootObjects(objInfo);
		else  SCENEMANAGER->AddSouthShootObjects(objInfo);
		m_arrowSpawnTime = GetTickCount();
	}

}


void CObject::Update(float time)
{
	m_time = time;
	m_elapsedLifeTime += m_time;

	if (m_objInfo.objType == OBJTYPE::OBJECT_BUILDING) this->SpawnBullet();
	if (m_objInfo.objType == OBJTYPE::OBJECT_CHARACTER) this->SpawnArrow();

	this->Move();
}