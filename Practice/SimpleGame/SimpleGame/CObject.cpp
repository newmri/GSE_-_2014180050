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
	case 0: m_vPos.x = speed; break;
	case 1: m_vPos.x = -speed; break;
	case 2: m_vPos.y = speed; break;
	case 3: m_vPos.y = -speed; break;
	case 4: m_vPos.x = speed; m_vPos.y = speed; break;
	case 5: m_vPos.x = speed; m_vPos.y = -speed; break;
	case 6: m_vPos.x = -speed; m_vPos.y = speed; break;
	case 7: m_vPos.x = -speed; m_vPos.y = -speed; break;
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