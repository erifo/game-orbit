#ifndef GOAL_H
#define GOAL_H

#include "sprite.h"
#include <string>

/*! Inheritates from the Sprite class. */
class Goal : public Sprite
{
	public:
	/*! Public constructor for goal.*/
		Goal(SDL_Renderer* renderer, std::string filename, int x=0, int y=0);
};

#endif