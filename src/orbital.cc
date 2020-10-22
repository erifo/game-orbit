#include <cmath>
#include "orbital.h"

Orbital::Orbital(SDL_Renderer* renderer, std::string filename, int x, int y)
	: Sprite(renderer, filename, x, y), x_center{x}, y_center{y},
		d_angle{0}, c_angle{0}, radius{0} {}

void Orbital::set_parameters(double i_radius, double i_speed)
{
	radius = i_radius;
	d_angle = i_speed;
	c_angle = 0;
}

void Orbital::set_orbit_mid(int x, int y)
{
	x_center = x;
	y_center = y;
}

void Orbital::update()
{
	c_angle += d_angle;
	set_x_mid(std::cos(c_angle) * radius + x_center);
	set_y_mid(std::sin(c_angle) * radius + y_center);
}