#include "bubble.h"

Bubble::Bubble(SDL_Renderer* renderer, std::string filename, int x, int y)
	: Orbital(renderer, filename, x, y), x_resting{x}, y_resting{y},
		resting{true}, godmode{false}
		
/*!
Sets the bubble's width and height.
*/
{
	set_w(25);
	set_h(25);
}
/*!
checks the bubble's position. 
If it's resting, it haven't been clicked by player, then it will remain at the resting position. 
Else the bubble's recent position will be updated.
*/
void Bubble::update()
{
	if (resting)
	{
		set_x_mid(x_resting);
		set_y_mid(y_resting);
	}
	else
	{ Orbital::update(); }
}

/*!
The setters for bubble. 
We set values to the variables.
*/
void Bubble::set_x_resting(int x)  /*! Sets a int to x-coordinate of resting position*/
{ x_resting = x; }

void Bubble::set_y_resting(int y)  /*! Sets a int to y-coordinate of resting position*/
{ y_resting = y; }

void Bubble::set_resting(bool state)  /*! Sets a bool, truth or false, to resting position. */
{ resting = state; }

void Bubble::set_god(bool state)   /*! Sets a bool to god mode. */
{ godmode = state; }

/*!
The getters for bubble. 
We get the values from the variables.
*/
int Bubble::get_x_resting() const   /*! Gets the int of x-coordinate from resting position*/
{ return x_resting; }

int Bubble::get_y_resting() const   /*! Gets the int of y-coordinate from resting position*/
{ return y_resting; }

bool Bubble::is_resting() const     /*! Gets the bool of resting position. */
{ return resting; }

bool Bubble::is_god() const         /*! Gets the bool of god mode. */
{ return godmode; }