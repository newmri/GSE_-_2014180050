#include "stdafx.h"
#include "Define.h"
#include "CFactory.h"
#include "Objects.h"

CFactory* CFactory::m_instance = nullptr;

shared_ptr<CObject> CFactory::CreateObj(ObjectInfo objinfo)
{
	shared_ptr<CObject> p = nullptr;

	switch (objinfo.objType) {
	case OBJTYPE::OBJECT_BUILDING: p = make_unique<CObject>(); break;
	case OBJTYPE::OBJECT_CHARACTER: p = make_unique<CObject>(); break;
	case OBJTYPE::OBJECT_BULLET: p = make_unique<CObject>(); break;
	default: break;
	}

	p->Init(objinfo);
	return move(p);
}