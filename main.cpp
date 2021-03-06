#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <ctime>
#include "field.hpp"
#include "snake.hpp"

bool quit;
int interval;

// keys
#define TURN_NORTH 'w'
#define TURN_SOUTH 's'
#define TURN_WEST 'a'
#define TURN_EAST 'd'
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
		case CHANGE_SPEED:
			system("cls");
			std::cout << "Enter the interframe interval (in milliseconds): ";
			std::cin >> interval;
			return;
		case QUIT:
			quit = true;
			return;
	}
}

void generate_food(Field *f)
{
	srand(time(0));
	int x = rand() % f->sizeX;
	int y = rand() % f->sizeY;
	while (f->getcell(x,y)->object == SNAKE_CHAR)
	{
		x = rand() % f->sizeX;
		y = rand() % f->sizeY;
	}
	f->getcell(x,y)->object = FOOD_CHAR;
}

void logic(Field *f, Snake *s)
{
	switch(s->checkmove())
	{
		case SNAKE_DIED:
			f->draw();
			std::cout << "length: " << s->cells.size();
			quit = true;
			return;;
		case SNAKE_ATE_FOOD:
			s->grow();
			generate_food(f);
			break;
	}
	s->move();
}

int main()
{
	interval = 75;
	quit = false;
	Field f(20, 20);
	Snake s(&f, f.sizeX/2, f.sizeY/2, Vector{0,0});
	generate_food(&f);

	while (true)
	{
		if (quit) return 0;
		f.draw();
		std::cout << "length: " << s.cells.size();
		Sleep(interval);
		system("cls");
		if (kbhit()) input(&s);
		logic(&f, &s);
	}

	return 0;
}