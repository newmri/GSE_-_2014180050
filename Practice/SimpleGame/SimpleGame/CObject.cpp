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

void CObject::Update()
{
	m_pos = m_pos + m_vPos * (1.0f / 1000.0f);
}