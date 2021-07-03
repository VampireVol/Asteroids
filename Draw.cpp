#include "Draw.h"
#include "Engine.h"
#include <math.h>

void recalc_pixel_position(int& x, int& y)
{
  if (x >= SCREEN_WIDTH)
    x -= SCREEN_WIDTH;
  else if (x < 0)
    x += SCREEN_WIDTH;
  if (y >= SCREEN_HEIGHT)
    y -= SCREEN_HEIGHT;
  else if (y < 0)
    y += SCREEN_HEIGHT;
}

void set_pixel(int x, int y, int color)
{
  recalc_pixel_position(x, y);
  if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
    buffer[y][x] = color;
}

void draw_dot(int x, int y, int color, int thickness)
{
  for (int i = 1 - thickness; i < thickness; ++i)
  {
    for (int j = 1 - thickness + abs(i); j < thickness - abs(i); ++j)
      set_pixel(x + j, y + i, color);
  }
}

void draw_line(int x0, int y0, int x1, int y1, int color)
{
  int dx = abs(x1 - x0);
  int sign_x = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sign_y = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2;

  while (true) {
    set_pixel(x0, y0, color);
    if (x0 == x1 && y0 == y1)
      break;
    e2 = 2 * err;
    if (e2 >= dy)
    {
      err += dy;
      x0 += sign_x;
    }
    if (e2 <= dx)
    {
      err += dx;
      y0 += sign_y;
    }
  }
}

void draw_thick_line(int x0, int y0, int x1, int y1, int color, int thickness)
{
  draw_line(x0, y0, x1, y1, color);
  draw_dot(x0, y0, color, thickness);
  draw_dot(x1, y1, color, thickness);
  for (int i = 1; i < thickness; ++i)
  {
    draw_line(x0, y0 - i, x1, y1 - i, color);
    draw_line(x0, y0 + i, x1, y1 + i, color);
  }
  for (int i = 1; i < thickness; ++i)
  {
    draw_line(x0 - i, y0, x1 - i, y1, color);
    draw_line(x0 + i, y0, x1 + i, y1, color);
  }
}