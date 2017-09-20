#include "stdafx.h"
#include "Define.h"
#include "CFactory.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;

unique_ptr<CObject> CFactory::CreateObj(const OBJTYPE objType, const Pos pos,
										const float size, const Color color)
{
	unique_ptr<CObject> p = nullptr;

	switch (objType) {
	case OBJTYPE::OBJECT: p = make_unique<CObject>(); break;
	default: break;
	}

	p->Init(objType, pos, size, color);
	return move(p);
}