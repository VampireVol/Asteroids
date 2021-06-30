#pragma once
#include "Point.h"

#include <vector>

using std::vector;

class Player
{
public:
	Player(int x, int y);
	void draw();
	void turn_right(float dt);
	void turn_left(float dt);
	void flying(float dt);
	void thrust(float dt);
private:
	Point _position;
	Point _velocity;
	float _angle;
	vector<Point> _ship_points;
	vector<Point> _draw_points;
	vector<Point> _collision_points;

	void rotate_points();
};

