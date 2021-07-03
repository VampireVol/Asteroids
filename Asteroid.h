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
private:
	const int _step_radius = 20;

	int _size;
	int _radius;
	vector<Point> _start_points;
	vector<Point> _draw_points;


};

