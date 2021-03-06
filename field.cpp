#include "field.hpp"
#include <string>
#include <iostream>

// toric field
Cell* Field::getcell(int x, int y)
{
	if (x >= sizeX && y >= 0 && y < sizeY) return getcell(-(sizeX-x), y);
	if (x < 0 && y >= 0 && y < sizeY) return getcell(sizeX+x, y);
	if (x >= 0 && x < sizeX && y >= sizeY) return getcell(x, -(sizeY-y));
	if (x >= 0 && x < sizeX && y < 0) return getcell(x, sizeY+y);
	if (x < 0 && y < 0) return getcell(sizeX+x, sizeY+y);
	if (x >= sizeX && y >= sizeY) return getcell(-(sizeX-x), -(sizeY-y));
	if (x < 0 && y >= sizeY) return getcell(sizeX+x, -(sizeY-y));
	if (x >= sizeX && y < 0) return getcell(-(sizeX-x), sizeY+y);
	if (x < 0 || y < 0 || x > sizeX || y > sizeY) return nullptr;
	return &cells[x * sizeY + y];
}

void Field::movecell(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 && y1 == y2) return;
	if (!getcell(x1,y1) || !getcell(x2,y2)) return;
	getcell(x2,y2)->object = getcell(x1,y1)->object;
	getcell(x1,y1)->object = EMPTY_CELL_CHAR;
}

Field::Field(int sx, int sy) : sizeX(sx), sizeY(sy)
{
	cells = new Cell[sizeX * sizeY];

	for (int x = 0; x < sizeX; ++x)
		for (int y = 0; y < sizeY; ++y)
		{
			getcell(x,y)->x = x;
			getcell(x,y)->y = y;
			getcell(x,y)->object = EMPTY_CELL_CHAR;
		}
}

Field::~Field()
{
	delete[] cells;
}

void Field::draw()
{
	std::string render;
	render += '#';
	for (int x = 0; x < sizeX; ++x)
		render += '#';
	render += "#\n";
	for (int y = sizeY-1; y >= 0; --y)
	{
		render += '#';
		for (int x = 0; x < sizeX; ++x)
			getcell(x,y) ? render += getcell(x,y)->object : render += EMPTY_CELL_CHAR;
		render += "#\n";
	}
	render += '#';
	for (int x = 0; x < sizeX; ++x)
		render += '#';
	render += "#\n";
	std::cout << render;
}