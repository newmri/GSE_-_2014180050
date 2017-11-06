#include "stdafx.h"
#include "CObject.h"
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
		m_bulletSpawnTime = GetTickCount();
		speed = BUILDING_SPEED;
		break;
	case OBJTYPE::OBJECT_CHARACTER: m_objInfo.life = CHARACTER_LIFE;  speed = CHARACTER_SPEED; break;
	case OBJTYPE::OBJECT_BULLET: m_objInfo.life = BULLET_LIFE; speed = BULLET_SPEED; break;
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
		if (m_objInfo.objType == OBJTYPE::OBJECT_BUILDING) {
			this->GotDamage(other->GetLife());
			other->SetDie();
		}
		switch(other->GetObjType()){
		case OBJTYPE::OBJECT_BUILDING:
			this->SetDie();
			other->GotDamage(m_objInfo.life);
			break;
		case OBJTYPE::OBJECT_BULLET:
			this->GotDamage(other->GetLife());
			other->SetDie();
			break;
		default: break;
		}
		this->SetColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		other->SetColor(Color(1.0f, 0.0f, 0.0f, 1.0f));

	}

}

void CObject::Move()
{
	if ((m_objInfo.pos.x + (m_objInfo.size / 2) > WINDOW_WIDTH / 2) || // End of Right
		((m_objInfo.pos.x - (m_objInfo.size / 2) <  WINDOW_WIDTH / 2.0 * -1.0f))) // End of Left
		m_vPos.x = -m_vPos.x;

	if ((m_objInfo.pos.y + (m_objInfo.size / 2) > WINDOW_HEIGHT / 2) || // End of Top
		((m_objInfo.pos.y - (m_objInfo.size / 2) <  WINDOW_HEIGHT / 2.0 * -1.0f))) // End of Bottom
		m_vPos.y = -m_vPos.y;
	
	m_objInfo.pos = m_objInfo.pos + m_vPos * (m_time / 1000.0f);
}

void CObject::SpawnBullet()
{
	ObjectInfo objInfo(OBJTYPE::OBJECT_BULLET, m_objInfo.pos, BULLET_SIZE, Color(1.0f,0.0f,0.0f,1.0f));
	m_bullet.emplace_back(FACTORYMANAGER->CreateObj(objInfo));
}

void CObject::Update(float time)
{
	m_time = time;
	m_elapsedLifeTime += m_time;
	if (m_objInfo.objType == OBJTYPE::OBJECT_BUILDING) {
		if (m_bulletSpawnTime + BULLET_SPAWN_TIME < GetTickCount()) {
			this->SpawnBullet();
			m_bulletSpawnTime = GetTickCount();
		}
		for (auto& d : m_bullet) d->Update(time);
		vector<shared_ptr<CObject>>::iterator itor = m_bullet.begin();
		while (itor != m_bullet.end()) {
			if ((*itor)->DoHavetoBeRemoved()) itor = m_bullet.erase(itor);
			else ++itor;
		}
		
		
	}
	else this->Move();
}