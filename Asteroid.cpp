#include "Asteroid.h"
#include "Draw.h"

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
	{
		_draw_points.push_back(_start_points[i]);
		_global_points.push_back(_start_points[i]);
	}
		
}

void Asteroid::draw()
{
	auto size = _draw_points.size();
	for (int i = 0; i < size; ++i)
	{
		int j = i + 1;
		draw_thick_line(
			static_cast<int>(_global_points[i % size].x),
			static_cast<int>(_global_points[i % size].y),
			static_cast<int>(_global_points[j % size].x),
			static_cast<int>(_global_points[j % size].y),
			0xffffff, 2);
	}
}

void Asteroid::update(float dt)
{
	move(dt);
	_angle += 0.5f * dt;
	auto size = _draw_points.size();
	for (int i = 0; i < size; ++i)
	{
		_draw_points[i].x = _start_points[i].x * cosf(_angle) - _start_points[i].y * sinf(_angle);
		_draw_points[i].y = _start_points[i].x * sinf(_angle) + _start_points[i].y * cosf(_angle);
		_global_points[i].x = _draw_points[i].x + _position.x;
		_global_points[i].y = _draw_points[i].y + _position.y;
	}
}

bool Asteroid::is_collided(const vector<Point> points)
{
	for (auto point : points)
	{
		bool answer = false;
		int size = _draw_points.size();
		for (int i = 0, j = size - 1; i < size; j = i++)
		{
			if ((((_global_points[i].y <= point.y) && (point.y < _global_points[j].y)) ||
				((_global_points[j].y <= point.y) && (point.y < _global_points[i].y))) &&
				(((_global_points[j].y - _global_points[i].y) != 0) &&
					(point.x > ((_global_points[j].x - _global_points[i].x) * (point.y - _global_points[i].y) / (_global_points[j].y - _global_points[i].y) + _global_points[i].x))))
				answer = !answer;
		}
		if (answer)
			return true;
	}
	return false;
}

int Asteroid::get_size()
{
	return _size;
}
