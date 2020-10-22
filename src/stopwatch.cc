#include "stopwatch.h"
#include <cmath>
#include <iostream>

Stopwatch::Stopwatch(std::string text, SDL_Renderer* renderer)
	: Text(text, renderer), origin_t{}, current_t{}, delta_t{0}, running{false} {}

void Stopwatch::start()
{
	time(&origin_t);
	running = true;
}

void Stopwatch::stop()
{
	running = false;
}

void Stopwatch::update()
{
	if (running)
	{
		time(&current_t);
		delta_t = current_t -  origin_t;
	}
}

bool Stopwatch::is_running()
{
	return running;
}

int Stopwatch::get_time()
{
	return delta_t;
}
