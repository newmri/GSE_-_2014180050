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
	m_vPos.x = SPEED;
}

void CObject::Update()
{
	m_pos = m_pos + m_vPos * (1.0f / 1000.0f);
}