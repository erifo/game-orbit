#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <string>
#include "spike.h"

class Projectile : public Spike
{
	private:
		char direction; /*! Character saving direction. [u,d,l,r] */

	public:
		Projectile(SDL_Renderer* renderer, std::string filename, char dir='u', int x=0, int y=0);
		
		/*! Called each frame. Changes position relative to direction. */
		void update() override;
		
		/*!
		    Rotates projectile relative to direction and
		    adds projectile to specified renderer.
		*/
		void draw(SDL_Renderer* renderer) override;
};

#endif