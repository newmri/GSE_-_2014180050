#include "stdafx.h"
#include "CObject.h"

void CObject::Init(const OBJTYPE newObjType, const Pos newPos,
				   const float newSize, const Color newColor)
{
	m_objType = newObjType;
	m_pos = newPos;
	m_color = newColor;
	m_size = newSize;
}