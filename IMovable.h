#pragma once
#include "Point.h"
class IMovable
{
public:
	IMovable(const Point &position, const Point &velocity, float angle);
	virtual ~IMovable() = default;
	float get_angle();
	Point get_position();
protected:
	Point _position;
	Point _velocity;
	float _angle;

	void move(float dt);
};

