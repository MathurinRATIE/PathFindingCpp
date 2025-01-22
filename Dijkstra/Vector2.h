#pragma once
#include <string>

struct Vector2
{
	float x, y;
	Vector2(float _x = 0, float _y = 0) :x(_x), y(_y) {}

	void SetX(float _x)
	{
		x = _x;
	}
	void SetY(float _y)
	{
		y = _y;
	}

	bool operator==(const Vector2& goal) const
	{
		return x == goal.x && y == goal.y;
	}

	bool operator!=(const Vector2& goal) const
	{
		return x != goal.x || y != goal.y;
	}

	Vector2 operator-(const Vector2& vector2) const
	{
		return Vector2(x - vector2.x, y - vector2.y);
	}

	float SqrDistance()
	{
		return sqrt(x * x + y * y);
	}

	std::string ToString()
	{
		return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}
};