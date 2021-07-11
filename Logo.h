#pragma once
#include "Point.h"
#include "Draw.h"
class Logo
{
public:
  Logo(Point position);
  void draw();
  void update(float dt);
  bool is_half_color();
  bool is_shaded();
private:
  Point _position;
  int _color;
  float _timer = 0.03f;
  float _shade_timer = 3.0f;

  void draw_symbol(char symbol, Point position, int width, int height, int color, int thickness);
};

