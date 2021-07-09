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
	void destroyed();
	void reset();
  Point get_shoot_pos();
  const vector<Point>& get_global_points();
private:
	vector<Point> _ship_points;
	vector<Point> _draw_points;
	vector<Point> _global_points;
	vector<Point> _thrust_points;
	vector<Point> _draw_thrust_points;
	const float _reloading_time = 0.2f;
	const float _flicker_time = 0.75f;
	const float _invulnerability_time = 5.0f;
	float _cur_reloading_time = 0.0f;
	float _cur_flicker_time = 0.0f;
	float _cur_invulnerability_time = 0.0f;
	int _lifes = 3;
	bool _thrust = false;

	void rotate_points();
	void reloading(float dt);
	void invulnerability(float dt);
	void clear();
};

