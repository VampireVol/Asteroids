#pragma once
#include "Point.h"
#include "Draw.h"
#include <math.h>
class Bullet
{
public:
	Bullet(const Point &position, float angle, float speed);
	void draw();
	void update(float dt);
	bool is_lifetime_over();
private:
	Point _position;
	float _angle;
	Point _velocity;
	
	float _lifetime = 5.0f;

	void move(float dt);
};

