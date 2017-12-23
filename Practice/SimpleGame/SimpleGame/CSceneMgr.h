#pragma once

#include "Define.h"
#include "Renderer.h"
#include "Objects.h"
#include "Sound.h"

class CSceneMgr
{
public:
	static CSceneMgr* GetInstance()
	{
		if (m_instance == nullptr) {
			m_instance = new CSceneMgr;
			m_instance->Init();
		}

		return m_instance;
	}
public:
	void Init();
	void InitNorthTeam();
	void InitSouthTeam();
	void InitRenderer()
	{
		m_renderer = make_unique<Renderer>(WINDOW_WIDTH, WINDOW_HEIGHT);
		if (!m_renderer->IsInitialized()) {
			std::cout << "Renderer could not be initialized.. \n";
			while (true);
		}

		cout << "Renderer is initialized!" << endl;
	}
public:

	void AddNorthObject(shared_ptr<CObject> obj){ m_objects[NORTH].emplace_back(obj); }
	void AddSouthObject(shared_ptr<CObject> obj) { m_objects[SOUTH].emplace_back(obj); }

public:
	void CheckCollision();
	void RemoveObject();

public:
	void Update(float time);

public:
	void Render();

public:
	const vector<shared_ptr<CObject>> GetNorthObjects() { return m_objects[NORTH]; }
	const unsigned int GetID() { return m_id++; }

public:
	void AddNorthShootObjects(const ObjectInfo& obj)
	{
		m_shootObjects[NORTH].emplace_back(FACTORYMANAGER->CreateObj(obj)); 
		if(obj.objType == OBJECT_BULLET) m_sound->PlaySounds(m_bulletShotSound, false, 0.15f);
	}
	void AddSouthShootObjects(const ObjectInfo& obj)
	{
		m_shootObjects[SOUTH].emplace_back(FACTORYMANAGER->CreateObj(obj)); 
		if (obj.objType == OBJECT_BULLET) m_sound->PlaySounds(m_bulletShotSound, false, 0.15f);
	};

public:
	void CreateNorthCharacter();
	bool CanCreateSouthCharacter()
	{
		if (m_characterTime[SOUTH] + SOUTH_CHARACTER_TIME < GetTickCount()) {
			m_characterTime[SOUTH] = GetTickCount();
			return true;
		}

		return false;
	}

public:
	void PlayeSpawnSound() { m_sound->PlaySounds(m_characterSpawnSound, false, 0.5f); }

public:
	int LoadImages(char* filePath) { return m_renderer->CreatePngTexture(filePath); }
private:
	static CSceneMgr* m_instance;
	vector<shared_ptr<CObject>> m_objects[2];
	vector<shared_ptr<CObject>> m_shootObjects[2];
	DWORD m_time;
	DWORD m_characterTime[2];
	float m_rainTime;
	shared_ptr<Renderer> m_renderer;
	unsigned int m_id;
	Sound* m_sound;
	int m_bulletShotSound;
	int m_characterSpawnSound;

};