#ifndef SPIKE_H
#define SPIKE_H

#include <string>
#include "sprite.h"

class Spike : public Sprite
{
	protected:
		std::string name; /*! Used to ID a general spike. */

	public:
		Spike(SDL_Renderer* renderer, std::string filename, int x=0, int y=0);
		
		/*! Virtual, so children-function will be used. */
		virtual void update();
		
		/*! Gets the name for convenient ID comparison. */
		std::string get_name();
		
		/*! Can be called to determine if it should be deleted. */
		bool delete_me{false};
};

#endif