#include "Engine.h"
#include "Player.h"
#include "Draw.h"

Player::Player(int x, int y)
	: _position({ (float)x, (float)y }), _velocity({ 0, 0 }), _angle(0)
{
	_ship_points.push_back({ 0, -50 });
	_ship_points.push_back({ 30, 30 });
	_ship_points.push_back({ 0, 10 });
	_ship_points.push_back({ -30, 30 });
	for (int i = 0; i < _ship_points.size(); ++i)
		_draw_points.push_back(_ship_points[i]);
}

void Player::draw()
{
	int size = _ship_points.size();
	for (int i = 0; i < size; ++i)
	{
		int j = i + 1;
		draw_thick_line(
			_draw_points[i % size].x + _position.x, _draw_points[i % size].y + _position.y,
			_draw_points[j % size].x + _position.x, _draw_points[j % size].y + _position.y, 
			0xffff00, 3);
	}
}

void Player::turn_right(float dt)
{
	_angle += 5.0f * dt;
	rotate_points();
}

void Player::turn_left(float dt)
{
	_angle -= 5.0f * dt;
	rotate_points();
}

void Player::flying(float dt)
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

void Player::thrust(float dt)
{
	_velocity.x += sinf(_angle) * 100.0f * dt;
	_velocity.y -= cosf(_angle) * 100.0f * dt;
}

void Player::rotate_points()
{
	int size = _ship_points.size();
	for (int i = 0; i < size; ++i)
	{
		_draw_points[i].x = _ship_points[i].x * cosf(_angle) - _ship_points[i].y * sinf(_angle);
		_draw_points[i].y = _ship_points[i].x * sinf(_angle) + _ship_points[i].y * cosf(_angle);
	}
}
