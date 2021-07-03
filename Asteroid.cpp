#include "Asteroid.h"
#include "Draw.h"
#include <math.h>

float pi() { return atan(1) * 4; }

Asteroid::Asteroid(const Point& position, float angle, float speed, int size)
	: IMovable(position, { sinf(angle) * speed, -cosf(angle) * speed }, angle), _size(size), _radius(size * _step_radius)
{
	int steps = 10;
	float angle_step = 2 * pi() / 10;
	float angle_cur = angle_step;
	for (int i = 0; i < 10; ++i)
	{
		float radius = (static_cast<float>(rand()) / RAND_MAX * 0.4f + 0.8f) * _radius;
		_start_points.push_back({ radius * cosf(angle_cur), radius * sinf(angle_cur) });
		angle_cur += angle_step;
	}
	for (int i = 0; i < _start_points.size(); ++i)
		_draw_points.push_back(_start_points[i]);
}

void Asteroid::draw()
{
	auto size = _draw_points.size();
	for (int i = 0; i < size; ++i)
	{
		int j = i + 1;
		draw_thick_line(
			static_cast<int>(_draw_points[i % size].x + _position.x),
			static_cast<int>(_draw_points[i % size].y + _position.y),
			static_cast<int>(_draw_points[j % size].x + _position.x),
			static_cast<int>(_draw_points[j % size].y + _position.y),
			0xffffff, 2);
	}
}

void Asteroid::update(float dt)
{
	_angle += 0.5f * dt;
	auto size = _draw_points.size();
	for (int i = 0; i < size; ++i)
	{
		_draw_points[i].x = _start_points[i].x * cosf(_angle) - _start_points[i].y * sinf(_angle);
		_draw_points[i].y = _start_points[i].x * sinf(_angle) + _start_points[i].y * cosf(_angle);
	}
	move(dt);
}
