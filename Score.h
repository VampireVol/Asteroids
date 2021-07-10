#pragma once
#include "Point.h"
#include <vector>

using std::vector;

class Score
{
public:
  Score();
  void add_score(int amount);
  int get_score();
  void draw();
  void reset();
private:
  int _amount;

  void draw_number(Point start, int height, int width, int number, int color = 0xffffff, int thickness = 3);
};

