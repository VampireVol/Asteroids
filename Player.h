#pragma once
#include "Point.h"
#include "IMovable.h"
#include <vector>

using std::vector;

class Player : public IMovable
{
public:
  Player(float x, float y);
  void draw();
  void draw_lifes();
  void turn_right(float dt);
  void turn_left(float dt);
  void update(float dt);
  void thrust(float dt);
  void set_thrust(bool thrust);
  bool is_thrust();
  bool is_reloaded();
  bool is_alive();
  bool is_invulnerability();
  bool is_flicker();
  void reload();
  void add_life();
  void destroyed();
  void reset();
  void reset_position();
  Point get_shoot_pos();
  const vector<Point>& get_global_points();
private:
  vector<Point> _ship_points;
  vector<Point> _draw_points;
  vector<Point> _global_points;
  vector<Point> _thrust_points;
  vector<Point> _draw_thrust_points;
  float _speed_rotation = 3.0f;
  float _reloading_time = 0.15f;
  float _flicker_time = 0.75f;
  float _invulnerability_time = 7.0f;
  float _cur_reloading_time = 0.0f;
  float _cur_flicker_time = 0.0f;
  float _cur_invulnerability_time = 0.0f;
  int _lifes = 0;
  bool _thrust = false;

  void update_draw_points();
  void update_global_points();
  void reloading(float dt);
  void invulnerability(float dt);
};

