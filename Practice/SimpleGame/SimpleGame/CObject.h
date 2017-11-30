#pragma once

#include "Enum.h"

#include <Windows.h>
#include <memory>
#include <vector>

struct Pos
{
	float x, y, z;
	Pos()
	{
		x = 0.0f, y = 0.0f, z = 0.0f;
	}

	Pos(float newX, float newY) : x(newX), y(newY) {};
	Pos(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {};

	Pos operator*(float time)
	{
		Pos pos(this->x * time, this->y * time, this->z * time);
		return pos;
	}
	Pos operator+(Pos pos)
	{
		Pos retPos(this->x + pos.x, this->y + pos.y, this->z + pos.z);
		return retPos;
	}

};

struct Color
{
	float r, g, b, a;
	Color()
	{
		r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
	}

	Color(float newR, float newG, float newB, float newA) : r(newR), g(newG), b(newB), a(newA) {};
};

struct ObjectInfo
{
	TEAMTYPE teamType;
	OBJTYPE objType;
	unsigned int id;
	unsigned int ownerId;
	Pos pos;
	float size;
	Color color;
	float life, maxLife;
	float renderLevel;

	ObjectInfo()
	{
		id = 0;
		ownerId = 0;
		size = 0.0f;
		life = 0.0f;
		maxLife = 0.0f;
		renderLevel = 0.0f;
	}

	ObjectInfo(unsigned int newId, unsigned int newOwnerId, TEAMTYPE newTeamType, OBJTYPE newObjType,
			   Pos newPos, float newSize, Color newColor, float newRenderLevel)
	{
		id = newId;
		ownerId = newOwnerId;
		teamType = newTeamType;
		objType = newObjType;
		pos = newPos;
		size = newSize;
		color = newColor;
		renderLevel = newRenderLevel;
	}
};

class CObject
{
public:
	/* For later time
	virtual void Init(const OBJTYPE newObjType, const Pos newPos,
		              const Color newColor, const float newSize) = 0;
					  
	virtual void Init() = 0;
	*/
	// For test
	void Init(const ObjectInfo objInfo);


	void Update(float time);
	void Move();
	// virtual void Update() = 0;

public:
	void CheckCollision(std::shared_ptr<CObject> other);
	void GotDamage(const float damage) { m_objInfo.life -= damage; }

public:
	const OBJTYPE& GetObjType() { return m_objInfo.objType; }
	const Pos& GetPos() { return m_objInfo.pos; }
	const Color& GetColor() { return m_objInfo.color; }
	const float& GetSize() { return m_objInfo.size; }
	const float& GetLife() { return m_objInfo.life; }
	const unsigned int& GetID() { return m_objInfo.id; }
	const unsigned int& GetOwnerID() { return m_objInfo.ownerId; }
	const TEAMTYPE& GetTeamType() { return m_objInfo.teamType; }
	const float& GetRenderLevel() { return m_objInfo.renderLevel; }
	const float GetLifePercent() { return m_objInfo.life / m_objInfo.maxLife; }
	const int& GetCol() { return m_col; }
	const int& GetRow() { return m_row; }
	const POINT& GetDir() { return m_dir; }
	const bool DoHavetoBeRemoved()
	{
		return (m_objInfo.life <= 0 || (m_elapsedLifeTime / 1000.0f >= m_lifeTime));
	}

public:
	void SetPos(const Pos newPos) { m_objInfo.pos = newPos; }
	void SetColor(const Color newColor) { m_objInfo.color = newColor; }
	void SetSize(const float newSize) { m_objInfo.size = newSize; }
	void SetDie() { m_objInfo.life = 0.0f; }

public:
	void SpawnBullet();
	void SpawnArrow();
	void RollBackColor() { m_objInfo.color = m_backUpColor; }

protected:
	ObjectInfo	    m_objInfo;
	Pos				m_vPos;
	Color			m_backUpColor;
	float			m_time;
	DWORD			m_bulletSpawnTime;
	DWORD			m_arrowSpawnTime;
	float			m_lifeTime, m_elapsedLifeTime;
	int				m_col, m_row;
	POINT			m_dir;

};