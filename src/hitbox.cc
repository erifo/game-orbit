#include <cmath>
#include <algorithm>
#include "hitbox.h"

Hitbox::Hitbox(int x, int y, int w, int h)
: rect{x, y, w, h} {}

//Spike-spike intersections.
bool Hitbox::intersects_with_rect(Hitbox* const& b) const
{
	return !(b->get_x() > get_x() + get_w())
	&& !(get_x() > b->get_x() + b->get_w())
	&& !(b->get_y() > get_y() + get_h())
	&& !(get_y() > b->get_y() + b->get_h());
}

//Bubble-* intersections.
bool Hitbox::intersects_with_circle(Hitbox* const& b) const
{
	int x_dist = b->get_x_mid() - get_x_mid();
	int y_dist = b->get_y_mid() - get_y_mid();
	double dist = std::sqrt(x_dist * x_dist + y_dist * y_dist);
	return !(dist > (b->radius + radius));
}

//Cursor-* intersections.
bool Hitbox::intersects_with_point(int const& x, int const& y) const
{
	return !(x > get_x() + get_w())
	&& !(get_x() > x)
	&& !(y > get_y() + get_h())
	&& !(get_y() > y);
}


//Setters
void Hitbox::set_x(int x)
{ rect.x = x; }

void Hitbox::set_y(int y)
{ rect.y = y; }

void Hitbox::set_w(int w)
{
	rect.w = w;
	radius = std::min(rect.w, rect.h) / 2;
}

void Hitbox::set_h(int h)
{
	rect.h = h;
	radius = std::min(rect.w, rect.h) / 2;
}

void Hitbox::set_x_mid(int x)
{ rect.x = x - (rect.w/2); }

void Hitbox::set_y_mid(int y)
{ rect.y = y - (rect.h/2); }


//Getters
SDL_Rect Hitbox::get_rect() const
{ return rect; }

int Hitbox::get_x() const
{ return rect.x; }

int Hitbox::get_y() const
{ return rect.y; }

int Hitbox::get_w() const
{ return rect.w; }

int Hitbox::get_h() const
{ return rect.h; }

int Hitbox::get_x_mid() const
{ return rect.x + (rect.w/2); }

int Hitbox::get_y_mid() const
{ return rect.y + (rect.h/2); }
