#include "Bullet.h"
#include "Engine.h"

Bullet::Bullet(const Point &position, float angle, float speed)
	: _position(position), _angle(angle), _velocity({ sinf(_angle) * speed, -cosf(_angle) * speed })
{
	//_velocity.x = ;
	//_velocity.y = ;
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

void Bullet::move(float dt)
{
	_position.x += _velocity.x * dt;
	_position.y += _velocity.y * dt;

	if (_position.x >= SCREEN_WIDTH)
		_position.x = 0;
	else if (_position.x < 0)
		_position.x = SCREEN_WIDTH - 1;
	if (_position.y >= SCREEN_HEIGHT)
		_position.y = 0;
	else if (_position.y < 0)
		_position.y = SCREEN_HEIGHT - 1;
}
