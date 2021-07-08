#pragma once
#include <math.h>

float pi();
void recalc_pixel_position(int& x, int& y);
void set_pixel(int x, int y, int color = 0xffffff);
void draw_dot(int x, int y, int color, int thickness = 1);
void draw_line(int x0, int y0, int x1, int y1, int color = 0xffffff);
void draw_thick_line(int x0, int y0, int x1, int y1, int color = 0xffffff, int thickness = 1);