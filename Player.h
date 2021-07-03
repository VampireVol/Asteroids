#pragma once
#include "Point.h"

#include <vector>

using std::vector;

class Player
{
public:
	Player(float x, float y);
	void draw();
	void turn_right(float dt);
	void turn_left(float dt);
	void update(float dt);
	void thrust(float dt);
	bool is_reloaded();
	void reload();
  Point get_shoot_pos();
  float get_angle();
private:
	Point _position;
	Point _velocity;
	float _angle;
	vector<Point> _ship_points;
	vector<Point> _draw_points;
	vector<Point> _collision_points;
	const float _reloading_time = 0.1f;
	float _cur_reloading_time = 0.0f;

	void rotate_points();
	void move(float dt);
	void reloading(float dt);
};

