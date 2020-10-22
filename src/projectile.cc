#include <iostream>
#include "projectile.h"

Projectile::Projectile(SDL_Renderer* renderer, std::string filename, char dir, int x, int y)
	: Spike(renderer, filename, x, y), direction{dir}
{
	name = "projectile";
	set_w(18);
	set_h(18);
}

void Projectile::update()
{
	if (direction == 'u') { set_y( get_y() - 1 ); }
	else if (direction == 'r') { set_x( get_x() + 1 ); }
	else if (direction == 'd') { set_y( get_y() + 1 ); }
	else if (direction == 'l') { set_x( get_x() - 1 ); }
}

void Projectile::draw(SDL_Renderer* renderer)
{
	if (enabled)
	{
		SDL_Rect r = get_rect();
		double angle{};
		if (direction == 'u')
		{ angle = 270.0; }
		else if (direction == 'r')
		{ angle = 0.0; }
		else if (direction == 'd')
		{ angle = 90.0; }
		else if (direction == 'l')
		{ angle = 180.0; }

		SDL_RenderCopyEx(renderer, texture, nullptr, &r, angle, NULL, SDL_FLIP_NONE);
	}
}
