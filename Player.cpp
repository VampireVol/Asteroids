#include "Engine.h"
#include "Player.h"
#include "Draw.h"
#include <iostream>

Player::Player(float x, float y)
  : IMovable({ x, y }, { 0, 0 }, 0),
  _ship_points({ { 0,-30 }, { 20, 20 }, { 0,15 }, { -20, 20 } }),
  _thrust_points({ { 0, 15 }, { 15, 30 }, { 5, 25 }, { 0, 35 }, { -5, 25 }, { -15, 30 } }),
  _draw_points(_ship_points.size(), { 0, 0 }),
  _global_points(_ship_points.size(), { 0, 0 }),
  _draw_thrust_points(_thrust_points.size(), { 0, 0 })
{
  update_draw_points();
  update_global_points();
}

void Player::draw()
{
  auto size = _thrust_points.size();
  if (is_thrust())
  {
    for (int i = 0; i < size; ++i)
    {
      int j = i + 1;
      draw_thick_line(
        static_cast<int>(_draw_thrust_points[i % size].x + _position.x),
        static_cast<int>(_draw_thrust_points[i % size].y + _position.y),
        static_cast<int>(_draw_thrust_points[j % size].x + _position.x),
        static_cast<int>(_draw_thrust_points[j % size].y + _position.y),
        0xff7700, 2);
    }
  }
  size = _ship_points.size();
  for (int i = 0; i < size; ++i)
  {
    int j = i + 1;
    draw_thick_line(
      static_cast<int>(_draw_points[i % size].x + _position.x),
      static_cast<int>(_draw_points[i % size].y + _position.y),
      static_cast<int>(_draw_points[j % size].x + _position.x),
      static_cast<int>(_draw_points[j % size].y + _position.y),
      0xffff00, 3);
  }
}

void Player::draw_lifes()
{
  Point start{ 10, 80 };
  int padding = 15;
  int height = 50;
  int width = 40;
  int color = 0xffff00;
  int thickness = 3;
  for (int i = 0; i < _lifes; ++i)
  {
    draw_thick_line(
      static_cast<int>(start.x + i * (width + padding) + 0.5f * width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + i * (width + padding) + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + i * (width + padding) + 0.5f * width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + i * (width + padding)),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + i * (width + padding) + 0.5f * width),
      static_cast<int>(start.y + 0.9f * height),
      static_cast<int>(start.x + i * (width + padding) + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + i * (width + padding) + 0.5f * width),
      static_cast<int>(start.y + 0.9f * height),
      static_cast<int>(start.x + i * (width + padding)),
      static_cast<int>(start.y + height), color, thickness);
  }
}

void Player::turn_right(float dt)
{
  _angle += _speed_rotation * dt;
  update_draw_points();
}

void Player::turn_left(float dt)
{
  _angle -= _speed_rotation * dt;
  update_draw_points();
}

void Player::update(float dt)
{
  move(dt);
  update_global_points();
  reloading(dt);
  invulnerability(dt);
}

void Player::thrust(float dt)
{
  _thrust = true;
  _velocity.x += sinf(_angle) * 100.0f * dt;
  _velocity.y -= cosf(_angle) * 100.0f * dt;
}

void Player::set_thrust(bool thrust)
{
  _thrust = thrust;
}

bool Player::is_thrust()
{
  return _thrust;
}

bool Player::is_reloaded()
{
  return _cur_reloading_time <= 0.0f;
}

bool Player::is_alive()
{
  return _lifes > 0;
}

bool Player::is_invulnerability()
{
  return _cur_invulnerability_time > 0;
}

bool Player::is_flicker()
{
  return _cur_flicker_time > _flicker_time * 0.75f;
}

void Player::reload()
{
  _cur_reloading_time = _reloading_time;
}

void Player::add_life()
{
  if (!_lifes)
  {
    reset_position();
    _cur_invulnerability_time = _invulnerability_time;
  }
  ++_lifes;
}

void Player::destroyed()
{
  --_lifes;
  _cur_invulnerability_time = _invulnerability_time;
  reset_position();
}

void Player::reset()
{
  _lifes = 3;
  _cur_invulnerability_time = 0;
  _cur_flicker_time = 0;
  reset_position();
}

void Player::reset_position()
{
  _position.x = SCREEN_WIDTH / 2;
  _position.y = SCREEN_HEIGHT / 2;
  _angle = 0;
  _velocity.x = 0;
  _velocity.y = 0;
  update_draw_points();
}

Point Player::get_shoot_pos()
{
  return { _draw_points[0].x + _position.x, _draw_points[0].y + _position.y };
}

const vector<Point>& Player::get_global_points()
{
  return _global_points;
}

void Player::update_draw_points()
{
  auto size = _ship_points.size();
  for (int i = 0; i < size; ++i)
  {
    _draw_points[i].x = _ship_points[i].x * cosf(_angle) - _ship_points[i].y * sinf(_angle);
    _draw_points[i].y = _ship_points[i].x * sinf(_angle) + _ship_points[i].y * cosf(_angle);
  }
  size = _thrust_points.size();
  for (int i = 0; i < size; ++i)
  {
    _draw_thrust_points[i].x = _thrust_points[i].x * cosf(_angle) - _thrust_points[i].y * sinf(_angle);
    _draw_thrust_points[i].y = _thrust_points[i].x * sinf(_angle) + _thrust_points[i].y * cosf(_angle);
  }
}

void Player::update_global_points()
{
  for (int i = 0; i < _global_points.size(); ++i)
  {
    _global_points[i].x = _draw_points[i].x + _position.x;
    _global_points[i].y = _draw_points[i].y + _position.y;
  }
}

void Player::reloading(float dt)
{
  if (!is_reloaded())
    _cur_reloading_time -= dt;
}

void Player::invulnerability(float dt)
{
  if (is_invulnerability())
  {
    if (_cur_flicker_time <= 0)
      _cur_flicker_time = _flicker_time;

    _cur_flicker_time -= dt;
    _cur_invulnerability_time -= dt;
  }
}
