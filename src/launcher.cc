#include <iostream>
#include "launcher.h"

Launcher::Launcher(SDL_Renderer* renderer, std::vector<Spike*>& new_spikes, std::string filename, char dir, int x, int y)
	: Spike(renderer, filename, x, y), new_spikes{new_spikes}, direction{dir},
			exit_point_x{0}, exit_point_y{0}, renderer{renderer}, timer{0}, timer_max{200}
{
	name = "launcher";
	set_w(60);
	set_h(60);
	reset();
	set_exit_point();
}

void Launcher::update()
{
	if (timer >= timer_max)
	{
		new_spikes.push_back(create_projectile());
		timer = 0;
	}
	++timer;
}

Projectile* Launcher::create_projectile()
{
	Projectile* projectile = new Projectile(renderer, "./img/projectile.png",
										direction, exit_point_x, exit_point_y);
	projectile->set_x_mid(exit_point_x);
	projectile->set_y_mid(exit_point_y);

	return projectile;
}

void Launcher::set_exit_point()
{
	if (direction == 'u')
	{
		exit_point_x = get_x_mid();
		exit_point_y = get_y() - 10; //10 should actually be half the height of a projectile.
	}
	else if (direction == 'r')
	{
		exit_point_x = get_x() + get_w() + 10;
		exit_point_y = get_y_mid();
	}
	else if (direction == 'd')
	{
		exit_point_x = get_x_mid();
		exit_point_y = get_y() + (get_h()) + 10;
	}
	else if (direction == 'l')
	{
		exit_point_x = get_x() - 10;
		exit_point_y = get_y_mid();
	}
}

void Launcher::draw(SDL_Renderer* renderer)
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

void Launcher::reset()
{
	timer = timer_max - 10;
}
