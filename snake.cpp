#include "snake.hpp"
#include "field.hpp"
#include <math.h>
#include <iostream>

#define HEAD cells.at(0)
#define LAST_ELEMENT cells.at(cells.size()-1)
#define PENULTIMATE_ELEMENT cells.at(cells.size()-2)

Snake::Snake(Field *f, int x, int y, Vector v) : field(f), move_vector(v)
{
	died = false;
	cells.push_back(f->getcell(x,y));
	HEAD->object = SNAKE_CHAR;
}

int Snake::checkmove()
{
	if (move_vector.x == 0 && move_vector.y == 0) return NOTHING_HAPPENED;
	if (!field->getcell(HEAD->x+move_vector.x, HEAD->y+move_vector.y)) return SNAKE_DIED;
	switch(field->getcell(HEAD->x+move_vector.x, HEAD->y+move_vector.y)->object)
	{
		case SNAKE_CHAR: return SNAKE_DIED;
		case FOOD_CHAR: return SNAKE_ATE_FOOD;
	}
	return NOTHING_HAPPENED;
}

void Snake::move()
{
	int previous_posX = HEAD->x;
	int previous_posY = HEAD->y;

	// moving the head
	field->movecell(HEAD->x, HEAD->y, HEAD->x+move_vector.x, HEAD->y+move_vector.y);
	HEAD = field->getcell(HEAD->x+move_vector.x, HEAD->y+move_vector.y);

	// moving the rest body
	for (int i = 1; i < cells.size(); ++i)
	{
		// temporary variables for saving needed values and nothing more
		int previous_posX1 = cells.at(i)->x;
		int previous_posY1 = cells.at(i)->y;

		field->movecell(cells.at(i)->x, cells.at(i)->y, previous_posX, previous_posY);
		cells.at(i) = field->getcell(previous_posX, previous_posY);
		previous_posX = previous_posX1;
		previous_posY = previous_posY1;
	}
}

void Snake::grow()
{
	if (cells.size() < 2)
	{
		if (move_vector.x == 0 && move_vector.y == 0) return;
		if (field->getcell(HEAD->x - move_vector.x, HEAD->y - move_vector.y))
		{
			cells.push_back(field->getcell(HEAD->x - move_vector.x, HEAD->y - move_vector.y));
			field->getcell(LAST_ELEMENT->x, LAST_ELEMENT->y)->object = SNAKE_CHAR;
		}
	}
	else if (field->getcell(LAST_ELEMENT->x + (LAST_ELEMENT->x - PENULTIMATE_ELEMENT->x),
							LAST_ELEMENT->y + (LAST_ELEMENT->y - PENULTIMATE_ELEMENT->y)))
	{
		if (field->getcell(LAST_ELEMENT->x + (LAST_ELEMENT->x - PENULTIMATE_ELEMENT->x),
							LAST_ELEMENT->y + (LAST_ELEMENT->y - PENULTIMATE_ELEMENT->y))->object == SNAKE_CHAR)
			return;
		cells.push_back(field->getcell(LAST_ELEMENT->x + (LAST_ELEMENT->x - PENULTIMATE_ELEMENT->x),
									   LAST_ELEMENT->y + (LAST_ELEMENT->y - PENULTIMATE_ELEMENT->y)));
		field->getcell(LAST_ELEMENT->x, LAST_ELEMENT->y)->object = SNAKE_CHAR;
	}
}

void Snake::make_turn()
{
	switch(checkmove())
	{
		case SNAKE_DIED:
			field->draw();
			std::cout << "length: " << cells.size();
			died = true;
			return;
		case SNAKE_ATE_FOOD:
			grow();
			move();
			field->generate_food();
			return;
	}
	move();
}


// Ночь коротка, цель далека,
// Ночью так часто хочется пить,
// Ты выходишь на кухню,
// Но вода здесь горька,
// Ты не можешь здесь спать,
// Ты не хочешь здесь жить.
//
// Доброе утро, последний герой!
// Доброе утро тебе и таким, как ты,
// Доброе утро, последний герой.
// Здравствуй, последний герой!
//
// Ты хотел быть один, это быстро прошло,
// Ты хотел быть один, но не смог быть один,
// Твоя ноша легка, но немеет рука,
// И ты встречаешь рассвет за игрой в дурака.
//
// Доброе утро, последний герой!
// Доброе утро тебе и таким, как ты,
// Доброе утро, последний герой.
// Здравствуй, последний герой!
//
// Утром ты стремишься скорее уйти,
// Телефонный звонок, как команда "Вперёд!"
// Ты уходишь туда, куда не хочешь идти,
// Ты уходишь туда, но тебя там никто не ждёт!
//
// Доброе утро, последний герой!
// Доброе утро тебе и таким, как ты,
// Доброе утро, последний герой.
// Здравствуй, последний герой!
//
// Цой жив.