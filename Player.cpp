#include "Engine.h"
#include "Player.h"
#include "Draw.h"
#include <iostream>

Player::Player(float x, float y)
	: IMovable({ x, y }, { 0, 0 }, 0)
{
	_ship_points.push_back({ 0, -30 });
	_ship_points.push_back({ 20, 20 });
	_ship_points.push_back({ 0, 15 });
	_ship_points.push_back({ -20, 20 });
	for (int i = 0; i < _ship_points.size(); ++i)
	{
		_draw_points.push_back(_ship_points[i]);
		_global_points.push_back(_ship_points[i]);
	}
		
}

void Player::draw()
{
	auto size = _ship_points.size();
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
	for (int i = 0; i < lifes; ++i)
	{
		draw_thick_line(start.x + i * (width + padding) + 0.5f * width, start.y, start.x + i * (width + padding) + width, start.y + height, color, thickness);
		draw_thick_line(start.x + i * (width + padding) + 0.5f * width, start.y, start.x + i * (width + padding), start.y + height, color, thickness);
		draw_thick_line(start.x + i * (width + padding) + 0.5f * width, start.y + 0.9f * height, start.x + i * (width + padding) + width, start.y + height, color, thickness);
		draw_thick_line(start.x + i * (width + padding) + 0.5f * width, start.y + 0.9f * height, start.x + i * (width + padding), start.y + height, color, thickness);
	}
}

void Player::turn_right(float dt)
{
	_angle += 2.0f * dt;
	rotate_points();
}

void Player::turn_left(float dt)
{
	_angle -= 2.0f * dt;
	rotate_points();
}

void Player::update(float dt)
{
	move(dt);
	for (int i = 0; i < _global_points.size(); ++i)
	{
		_global_points[i].x = _draw_points[i].x + _position.x;
		_global_points[i].y = _draw_points[i].y + _position.y;
	}
	reloading(dt);
}

void Player::thrust(float dt)
{
	_velocity.x += sinf(_angle) * 100.0f * dt;
	_velocity.y -= cosf(_angle) * 100.0f * dt;
}

bool Player::is_reloaded()
{
	return _cur_reloading_time <= 0.0f;
}

bool Player::is_alive()
{
	return lifes > 0;
}

void Player::reload()
{
	_cur_reloading_time = _reloading_time;
}

void Player::destroyed()
{
	--lifes;
	_position.x = 500;
	_position.y = 500;
}

Point Player::get_shoot_pos()
{
	return { _draw_points[0].x + _position.x, _draw_points[0].y + _position.y };
}

const vector<Point>& Player::get_global_points()
{
	return _global_points;
}

void Player::reloading(float dt)
{
	if (!is_reloaded())
		_cur_reloading_time -= dt;
}

void Player::rotate_points()
{
	auto size = _ship_points.size();
	for (int i = 0; i < size; ++i)
	{
		_draw_points[i].x = _ship_points[i].x * cosf(_angle) - _ship_points[i].y * sinf(_angle);
		_draw_points[i].y = _ship_points[i].x * sinf(_angle) + _ship_points[i].y * cosf(_angle);
	}
}
