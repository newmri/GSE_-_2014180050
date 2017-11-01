#pragma once

#include "Define.h"
#include "Renderer.h"

class CSceneMgr
{
public:
	CSceneMgr() { this->Init(); }
public:
	void Init();
	void InitRenderer() {
		m_renderer = make_unique<Renderer>(500, 500);
		if (!m_renderer->IsInitialized()) std::cout << "Renderer could not be initialized.. \n";
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