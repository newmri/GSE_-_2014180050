#pragma once

#include "Enum.h"

struct Pos
{
	float x, y, z;
	Pos()
	{
		x = 0.0f, y = 0.0f, z = 0.0f;
	}
	Pos(float newX, float newY, float newZ) : x(newX), y(newY), z(newZ) {};

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


	void Update() {};
	// virtual void Update() = 0;
public:
	const OBJTYPE& GetObjType() { return m_objType; }
	const Pos& GetPos() { return m_pos; }
	const Color& GetColor() { return m_color; }
	const float& GetSize() { return m_size; }

public:
	void SetPos(const Pos newPos) { m_pos = newPos; }
	void SetColor(const Color newColor) { m_color = newColor; }
	void SetSize(const float newSize) { m_size = newSize; }

private:
	OBJTYPE			m_objType;
	Pos				m_pos;
	Color			m_color;
	float			m_size;

};