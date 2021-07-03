#include "IMovable.h"
#include "Engine.h"

IMovable::IMovable(const Point& position, const Point& velocity, float angle)
	: _position(position), _velocity(velocity), _angle(angle)
{

}

void IMovable::move(float dt)
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
