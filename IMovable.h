#pragma once
#include "Point.h"
class IMovable
{
public:
	IMovable(const Point &position, const Point &velocity, float angle);
	virtual ~IMovable() = default;
protected:
	Point _position;
	Point _velocity;
	float _angle;

	void move(float dt);
};

