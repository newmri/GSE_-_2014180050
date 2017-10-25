#pragma once

#include "Enum.h"

#include <memory>


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

class CObject
{
public:
	/* For later time
	virtual void Init(const OBJTYPE newObjType, const Pos newPos,
		              const Color newColor, const float newSize) = 0;
					  
	virtual void Init() = 0;
	*/
	// For test
	void Init(const OBJTYPE newObjType, const Pos newPos,
		const float newSize, const Color newColor);


	void Update(float time);
	void Move();
	// virtual void Update() = 0;

public:
	void CheckCollision(std::shared_ptr<CObject> other);

public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const Pos& GetPos() { return m_pos; }
	const Color& GetColor() { return m_color; }
	const float& GetSize() { return m_size; }
	const float& GetLife() { return m_life; }
	const bool DoHavetoBeRemoved()
	{
		return (m_life <= 0 || (m_elapsedLifeTime / 1000.0f >= m_lifeTime));
	}

public:
	void SetPos(const Pos newPos) { m_pos = newPos; }
	void SetColor(const Color newColor) { m_color = newColor; }
	void SetSize(const float newSize) { m_size = newSize; }

protected:
	OBJTYPE			m_objType;
	Pos				m_pos;
	Pos				m_vPos;
	Color			m_color;
	float			m_size;
	float			m_time;
	float			m_life, m_lifeTime, m_elapsedLifeTime;

};