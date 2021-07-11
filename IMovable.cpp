#include "IMovable.h"
#include "Engine.h"
#include <math.h>

IMovable::IMovable(const Point& position, const Point& velocity, float angle)
  : _position(position), _velocity(velocity), _angle(angle)
{

}

float IMovable::get_angle()
{
  return _angle;
}

float IMovable::get_speed()
{
  return sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
}

Point IMovable::get_position()
{
  return _position;
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
