#pragma once
#include "Draw.h"
#include "IMovable.h"
#include <math.h>

class Bullet : IMovable
{
public:
	Bullet(const Point &position, float angle, float speed);
	void draw();
	void update(float dt);
	bool is_lifetime_over();
private:
	float _lifetime = 5.0f;
};

