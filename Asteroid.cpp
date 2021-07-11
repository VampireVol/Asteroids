#include "Asteroid.h"
#include "Draw.h"

Asteroid::Asteroid(const Point& position, float angle, float speed, float speed_rotation, int size, int color)
  : IMovable(position, { sinf(angle) * speed, -cosf(angle) * speed }, angle), 
  _speed_rotation(speed_rotation), _size(size), _radius(size* _step_radius), _health(size), _start_color(color), _color(color),
  _start_points(10, { 0, 0 }), _draw_points(10, { 0, 0 }), _global_points(10, { 0, 0 })
{
  auto n = _start_points.size();
  float angle_step = 2 * pi() / n;
  float angle_cur = angle_step;
  for (int i = 0; i < n; ++i)
  {
    float radius = (static_cast<float>(rand()) / RAND_MAX * 0.4f + 0.8f) * _radius;
    _start_points[i] = { radius * cosf(angle_cur), radius * sinf(angle_cur) };
    angle_cur += angle_step;
  }
  update_points();
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
      _color, 3);
  }
}

void Asteroid::update(float dt)
{
  move(dt);
  _angle += _speed_rotation * dt;
  update_points();
}

void Asteroid::get_damage()
{
  --_health;
  _color = shade_color(_color, -20);
}

bool Asteroid::is_collided(const vector<Point>& points)
{
  for (auto point : points)
  {
    bool answer = false;
    auto size = _draw_points.size();
    for (size_t i = 0, j = size - 1; i < size; j = i++)
    {
      if ((((_global_points[i].y <= point.y) && (point.y < _global_points[j].y)) ||
        ((_global_points[j].y <= point.y) && (point.y < _global_points[i].y))) &&
        (((_global_points[j].y - _global_points[i].y) != 0) &&
          (point.x > ((_global_points[j].x - _global_points[i].x) * (point.y - _global_points[i].y) /
            (_global_points[j].y - _global_points[i].y) + _global_points[i].x))))
        answer = !answer;
    }
    if (answer)
      return true;
  }
  return false;
}

bool Asteroid::is_destroyed()
{
  return _health <= 0;
}

int Asteroid::get_size()
{
  return _size;
}

int Asteroid::get_color()
{
  return _start_color;
}

void Asteroid::update_points()
{
  auto size = _draw_points.size();
  for (int i = 0; i < size; ++i)
  {
    _draw_points[i].x = _start_points[i].x * cosf(_angle) - _start_points[i].y * sinf(_angle);
    _draw_points[i].y = _start_points[i].x * sinf(_angle) + _start_points[i].y * cosf(_angle);
    _global_points[i].x = _draw_points[i].x + _position.x;
    _global_points[i].y = _draw_points[i].y + _position.y;
  }
}
