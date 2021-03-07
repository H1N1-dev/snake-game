#include <iostream>
#include <windows.h>
#include <conio.h>
#include "field.hpp"
#include "snake.hpp"

int interval;

// keys
#define TURN_NORTH 'w'
#define TURN_SOUTH 's'
#define TURN_WEST 'a'
#define TURN_EAST 'd'
#define TURN_NORTH_EAST 'o'
#define TURN_NORTH_WEST 'u'
#define TURN_SOUTH_WEST 'j'
#define TURN_SOUTH_EAST 'l'
#define QUIT 'q'
#define CHANGE_SPEED 'c'

void input(Snake *s)
{
	char input;
	input = getch();
	switch(input)
	{
		case TURN_NORTH:
			if (s->cells.size() > 1 && s->move_vector.y < 0) return;
			s->move_vector.x = 0;
			s->move_vector.y = 1;
			return;
		case TURN_SOUTH:
			if (s->cells.size() > 1 && s->move_vector.y > 0) return;
			s->move_vector.x = 0;
			s->move_vector.y = -1;
			return;
		case TURN_WEST:
			if (s->cells.size() > 1 && s->move_vector.x > 0) return;
			s->move_vector.y = 0;
			s->move_vector.x = -1;
			return;
		case TURN_EAST:
			if (s->cells.size() > 1 && s->move_vector.x < 0) return;
			s->move_vector.y = 0;
			s->move_vector.x = 1;
			return;
		case TURN_NORTH_EAST:
			if (s->cells.size() > 1 && (s->move_vector.y < 0 && s->move_vector.x < 0)) return;
			s->move_vector.x = 1;
			s->move_vector.y = 1;
			return;
		case TURN_NORTH_WEST:
			if (s->cells.size() > 1 && (s->move_vector.y < 0 && s->move_vector.x > 0)) return;
			s->move_vector.x = -1;
			s->move_vector.y = 1;
			return;
		case TURN_SOUTH_WEST:
			if (s->cells.size() > 1 && (s->move_vector.y > 0 && s->move_vector.x > 0)) return;
			s->move_vector.x = -1;
			s->move_vector.y = -1;
			return;
		case TURN_SOUTH_EAST:
			if (s->cells.size() > 1 && (s->move_vector.y > 0 && s->move_vector.x < 0)) return;
			s->move_vector.x = 1;
			s->move_vector.y = -1;
			return;
		case CHANGE_SPEED:
			system("cls");
			std::cout << "Enter the interframe interval (in milliseconds): ";
			std::cin >> interval;
			return;
		case QUIT:
			s->died = true;
			return;
	}
}

int main()
{
	interval = 75;
	Field f(20, 20);
	Snake s(&f, f.sizeX/2, f.sizeY/2, Vector{0,0});
	f.generate_food();

	while (true)
	{
		if (s.died) return 0;
		f.draw();
		std::cout << "length: " << s.cells.size();
		Sleep(interval);
		system("cls");
		if (kbhit()) input(&s);
		s.make_turn();
	}

	return 0;
}