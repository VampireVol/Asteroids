#pragma once
#include "Draw.h"
#include "IMovable.h"

class Bullet : IMovable
{
public:
	Bullet(const Point &position, float angle, float speed);
	void draw();
	void update(float dt);
	bool is_lifetime_over();
	Point get_position();
private:
	float _lifetime = 3.0f;
};

