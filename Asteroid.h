#pragma once
#include "IMovable.h"
#include <vector>

using std::vector;

class Asteroid : public IMovable
{
public:
  Asteroid(const Point& position, float angle, float speed, int size, int color);
  void draw();
  void update(float dt);
  void get_damage();
  bool is_collided(const vector<Point>& points);
  bool is_destroyed();
  int get_size();
  int get_color();
private:
  int _step_radius = 20;
  int _size;
  int _radius;
  int _health;
  int _start_color;
  int _color;
  vector<Point> _start_points;
  vector<Point> _draw_points;
  vector<Point> _global_points;

  void update_points();
  void shade_color(int amount);
};

