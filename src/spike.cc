#include "spike.h"

Spike::Spike(SDL_Renderer* renderer, std::string filename, int x, int y)
	: Sprite(renderer, filename, x, y), name{"spike"}, delete_me{false} {}

void Spike::update()
{
	//Virtual
}

std::string Spike::get_name()
{
	return name;
}
