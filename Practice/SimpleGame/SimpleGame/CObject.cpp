#include "stdafx.h"
#include "CObject.h"
#include "Define.h"

void CObject::Init(const OBJTYPE newObjType, const Pos newPos,
	const float newSize, const Color newColor)
{
	m_objType = newObjType;
	m_pos = newPos;
	m_color = newColor;
	m_size = newSize;
	m_life = LIFE;
	switch (rand() % 8) {
	case 0: m_vPos.x = SPEED; break;
	case 1: m_vPos.x = -SPEED; break;
	case 2: m_vPos.y = SPEED; break;
	case 3: m_vPos.y = -SPEED; break;
	case 4: m_vPos.x = SPEED; m_vPos.y = SPEED; break;
	case 5: m_vPos.x = SPEED; m_vPos.y = -SPEED; break;
	case 6: m_vPos.x = -SPEED; m_vPos.y = SPEED; break;
	case 7: m_vPos.x = -SPEED; m_vPos.y = -SPEED; break;
	}
}

void CObject::CheckCollision(shared_ptr<CObject> other)
{
	if (((m_pos.x + (m_size / 2)) > (other->GetPos().x - (m_size / 2))) && // Right
		((m_pos.x - (m_size / 2)) < (other->GetPos().x + (m_size / 2))) && // Left
		((m_pos.y + (m_size / 2)) > (other->GetPos().y - (m_size / 2))) && // Top
		((m_pos.y - (m_size / 2)) < (other->GetPos().y + (m_size / 2)))) { // Bottom
		this->SetColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		other->SetColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
	}

}

void CObject::Move()
{
	if ((m_pos.x + (m_size / 2) > WINDOW_WIDTH / 2) || // End of Right
		((m_pos.x - (m_size / 2) <  WINDOW_WIDTH / 2.0 * -1.0f))) // End of Left
		m_vPos.x = -m_vPos.x;

	if ((m_pos.y + (m_size / 2) > WINDOW_HEIGHT / 2) || // End of Top
		((m_pos.y - (m_size / 2) <  WINDOW_HEIGHT / 2.0 * -1.0f))) // End of Bottom
		m_vPos.y = -m_vPos.y;
		
	m_pos = m_pos + m_vPos * (m_time / 1000.0f);
}
void CObject::Update(float time)
{
	m_time = time;
	m_life -= 1;
	this->Move();
}