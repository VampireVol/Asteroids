#include "Logo.h"
#include <string>

using std::string;

Logo::Logo(Point position)
  : _position(position), _color(0xffffff)
{
}

void Logo::draw()
{
  string logo = "ASTEROIDS";
  auto size = logo.size();
  int padding = 30;
  int height = 160;
  int width = 80;
  for (int i = 0; i < size; ++i)
  {
    draw_symbol(logo[i], { _position.x + i * (width + padding), _position.y },
      width, height, _color, 8);
  }
}

void Logo::update(float dt)
{
  _timer -= dt;
  _shade_timer -= dt;
  if (_timer < 0)
  {
    _timer = 0.03f;
    _color = shade_color(_color, -5);
  }
}

bool Logo::is_half_color()
{
  return _color < 0x666666;
}

bool Logo::is_shaded()
{
  return _shade_timer < 0;
}

void Logo::draw_symbol(char symbol, Point start, int width, int height, int color, int thickness)
{
  switch (symbol)
  {
  case 'A':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.75f * height),
      static_cast<int>(start.x),
      static_cast<int>(start.y + 0.5f * height), color, thickness);
    break;
  case 'S':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x),
      static_cast<int>(start.y + 0.5f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + 0.5f * height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.5f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.5f * height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    break;
  case 'T':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + 0.5f * width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + 0.5f * width),
      static_cast<int>(start.y + height), color, thickness);
    break;
  case 'E':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + 0.5f * height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.5f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x),
      static_cast<int>(start.y), color, thickness);
    break;
  case 'R':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.5f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.5f * height),
      static_cast<int>(start.x),
      static_cast<int>(start.y + 0.5f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + 0.5f * width),
      static_cast<int>(start.y + 0.5f * height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    break;
  case 'O':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x),
      static_cast<int>(start.y), color, thickness);
    break;
  case 'I':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + 0.5f * width),
      static_cast<int>(start.y),
      static_cast<int>(start.x + 0.5f * width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x),
      static_cast<int>(start.y + height), color, thickness);
    break;
  case 'D':
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.1f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.1f * height),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.9f * height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + 0.9f * height),
      static_cast<int>(start.x),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y + height),
      static_cast<int>(start.x),
      static_cast<int>(start.y), color, thickness);
    break;
  default:
    draw_thick_line(
      static_cast<int>(start.x),
      static_cast<int>(start.y),
      static_cast<int>(start.x + width),
      static_cast<int>(start.y + height), color, thickness);
    draw_thick_line(
      static_cast<int>(start.x + width),
      static_cast<int>(start.y),
      static_cast<int>(start.x),
      static_cast<int>(start.y + height), color, thickness);
    break;
  }
}
