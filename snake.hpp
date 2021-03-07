#pragma once
#include <vector>
#include "field.hpp"

#define SNAKE_CHAR 'O'
#define FOOD_CHAR 'F'

#define NOTHING_HAPPENED 0
#define SNAKE_DIED 1
#define SNAKE_ATE_FOOD 2

struct Vector
{
	int x, y;
};

struct Snake
{
	Field *field;
	bool died;
	std::vector<Cell*> cells;
	Vector move_vector;
	Snake(Field *f, int x, int y, Vector v);
	int checkmove();
	void make_turn();
	void move();
	void grow();
};