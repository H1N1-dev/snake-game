#pragma once

#define EMPTY_CELL_CHAR ' '

struct Cell
{
	int x, y;
	char object;
};

struct Field
{
	int sizeX, sizeY;
	Cell *cells;

	Cell* getcell(int x, int y);
	void draw();
	void generate_food();
	void movecell(int x1, int y1, int x2, int y2);

	Field(int sx, int sy);
	~Field();
};