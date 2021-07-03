#include "Bullet.h"

Bullet::Bullet(const Point &position, float angle, float speed)
	: IMovable(position, { sinf(angle) * speed, -cosf(angle) * speed }, angle)
{

}

void Bullet::draw()
{
	draw_dot(_position.x, _position.y, 0xff0000, 4);
}

void Bullet::update(float dt)
{
	_lifetime -= dt;
	move(dt);
}

bool Bullet::is_lifetime_over()
{
	return _lifetime < 0.0f;
}
