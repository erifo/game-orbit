#include "goal.h"

/*! Handles the goal object.*/
Goal::Goal(SDL_Renderer* renderer, std::string filename, int x, int y)
	: Sprite(renderer, filename, x, y)
{
	set_w(60); /*! Sets the width for the goal object. */
	set_h(60); /*! Sets the height for the goal object. */
}