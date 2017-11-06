#pragma once

#include "Define.h"
#include "Renderer.h"

class CSceneMgr
{
public:
	CSceneMgr() { this->Init(); }
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
private:
	vector<shared_ptr<CObject>> m_objects;
	DWORD m_time;
	shared_ptr<Renderer> m_renderer;
};