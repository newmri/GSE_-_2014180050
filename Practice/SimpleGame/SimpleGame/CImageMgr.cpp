#include "stdafx.h"
#include "Define.h"
#include "Objects.h"

CImageMgr* CImageMgr::m_instance = nullptr;

void CImageMgr::Init()
{
	m_imageList.insert(make_pair("NorthBuilding", SCENEMANAGER->LoadImages("Resources\\North_Building.png")));
	m_imageList.insert(make_pair("SouthBuilding", SCENEMANAGER->LoadImages("Resources\\South_Building.png")));

	cout << "ImageManager is initialized!" << endl;
}