#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "hitbox.h"

class Sprite : public Hitbox
{
	protected:
		std::string filename; /*! Full path to .png file. */
		bool enabled; /*! Determines if sprite should be drawn. */
		SDL_Texture* texture; /*! Stores the converted surface for rendering. */
		
	public:
		Sprite(SDL_Renderer* renderer, std::string filename, int x=0, int y=0);
		virtual ~Sprite();
		Sprite(Sprite const&) = delete;
		Sprite& operator=(Sprite const& ) = delete;
		
		/*! Virtual, to prioritize child-function. */
		virtual void update();
		
		/*! Draws the sprite to specified renderer. */
		virtual void draw(SDL_Renderer* renderer);
    
        /*! Checks if the sprite is enabled. */
		bool is_enabled() const;
		
		/*! Decides if the sprite is enabled. */
		void set_enabled(bool state);
};

#endif