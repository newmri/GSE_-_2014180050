#pragma once

#include "Define.h"
#include "Renderer.h"
#include "Objects.h"

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
	void InitRenderer()
	{
		m_renderer = make_unique<Renderer>(WINDOW_WIDTH, WINDOW_HEIGHT);
		if (!m_renderer->IsInitialized()) {
			std::cout << "Renderer could not be initialized.. \n";
			while (true);
		}

		cout << "Renderer is initialized!" << endl;
	}
	void AddObject(shared_ptr<CObject> obj) { m_objects.emplace_back(obj); }

public:
	void CheckCollision();
	void RemoveObject();
	void Render();
	void Update(float time);

public:
	const vector<shared_ptr<CObject>> GetObjects() { return m_objects; }
	const unsigned int GetID() { return m_id++; }

public:
	void AddShootObjects(const ObjectInfo& obj) { m_shootObjects.emplace_back(FACTORYMANAGER->CreateObj(obj)); };

private:
	static CSceneMgr* m_instance;
	vector<shared_ptr<CObject>> m_objects;
	vector<shared_ptr<CObject>> m_shootObjects;
	DWORD m_time;
	shared_ptr<Renderer> m_renderer;
	unsigned int m_id;
	int m_buildingId;
};