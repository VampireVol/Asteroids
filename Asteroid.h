#pragma once
#include "IMovable.h"
#include <vector>

using std::vector;

class Asteroid : public IMovable
{
public:
	Asteroid(const Point& position, float angle, float speed, int size);
	void draw();
	void update(float dt);
	bool is_collided(const vector<Point> points);
	int get_size();
private:
	int _step_radius = 20;

	int _size;
	int _radius;
	vector<Point> _start_points;
	vector<Point> _draw_points;
	vector<Point> _global_points;


};

