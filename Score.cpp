#include "Score.h"
#include "Draw.h"

Score::Score()
	:_amount(0)
{
}

void Score::add_score(int amount)
{
	_amount += amount;
}

void Score::draw()
{
	Point start_pos{ 10, 10 };
	int padding = 10;
	int height = 50;
	int width = 25;
	int max_numbers = 8;
	int amount = _amount;
	for (int i = max_numbers - 1; i >= 0; --i)
	{
		if (amount > 0) 
		{
			draw_number({ start_pos.x + i * (width + padding), start_pos.y }, height, width, amount % 10);
			amount /= 10;
		}
		else
		{
			draw_number({ start_pos.x + i * (width + padding), start_pos.y }, height, width, 0);
		}
	}
}

void Score::reset()
{
	_amount = 0;
}

void Score::draw_number(Point start, int height, int width, int number, int color, int thickness)
{
	switch (number)
	{
	case 0:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x + width, start.y + height, start.x, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x, start.y, color, thickness);
		break;
	case 1:
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x + width, start.y + height, color, thickness);
		break;
	case 2:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x + width, start.y + 0.5f * height, start.x, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x + width, start.y + height, color, thickness);
		break;
	case 3:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x + width, start.y + height, start.x + width, start.y, color, thickness);
		break;
	case 4:
		draw_thick_line(start.x, start.y, start.x, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x + width, start.y + height, color, thickness);
		break;
	case 5:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x, start.y, start.x, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x + width, start.y + 0.5f * height, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x + width, start.y + height, color, thickness);
		break;
	case 6:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x, start.y, start.x, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x + width, start.y + 0.5f * height, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x + width, start.y + height, color, thickness);
		break;
	case 7:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x, start.y + height, color, thickness);
		break;
	case 8:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x, start.y, start.x, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x + width, start.y + height, color, thickness);
		break;
	case 9:
		draw_thick_line(start.x, start.y, start.x + width, start.y, color, thickness);
		draw_thick_line(start.x, start.y, start.x, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x, start.y + 0.5f * height, start.x + width, start.y + 0.5f * height, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x, start.y + height, start.x + width, start.y + height, color, thickness);
		break;
	default:
		draw_thick_line(start.x, start.y, start.x + width, start.y + height, color, thickness);
		draw_thick_line(start.x + width, start.y, start.x, start.y + height, color, thickness);
		break;
	}
}
