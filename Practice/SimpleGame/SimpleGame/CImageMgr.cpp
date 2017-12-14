#include "stdafx.h"
#include "Define.h"
#include "Objects.h"

CImageMgr* CImageMgr::m_instance = nullptr;

void CImageMgr::Init()
{
	m_imageList.insert(make_pair("BackGround", SCENEMANAGER->LoadImages("Resources\\BackGround.png")));
	m_imageList.insert(make_pair("NorthBuilding", SCENEMANAGER->LoadImages("Resources\\North_Building.png")));
	m_imageList.insert(make_pair("SouthBuilding", SCENEMANAGER->LoadImages("Resources\\South_Building.png")));
	m_imageList.insert(make_pair("NC", SCENEMANAGER->LoadImages("Resources\\North_Character.png")));
	m_imageList.insert(make_pair("SC", SCENEMANAGER->LoadImages("Resources\\South_Character.png")));
	m_imageList.insert(make_pair("Fire", SCENEMANAGER->LoadImages("Resources\\FireBulletEffect.png")));
	m_imageList.insert(make_pair("Ice", SCENEMANAGER->LoadImages("Resources\\IceBulletEffect.png")));
	m_imageList.insert(make_pair("Snow", SCENEMANAGER->LoadImages("Resources\\Snow.png")));
	cout << "ImageManager is initialized!" << endl;
}