#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "hitbox.h"

class Text
{
	private:
		static TTF_Font* font; /*! Font used to display the text. */
		int width; /*! Width of displayed text. */
		int height; /*! Height of displayed text. */

		Text(const Text& text) = delete;
		Text& operator=(const Text& text) = delete;
        
        /*!
            Prepares class-object for display.
            Loads ttf font, converts surface to texture among other things.
        */
		void init(std::string text, SDL_Renderer* renderer);

	public:
		SDL_Texture* texture; /*! Stores the text-filled texture. */
		std::string text; /*! Text intended to be displayed. */

		Text(std::string text, SDL_Renderer* renderer);
		Text(Text&& text);
		virtual ~Text();
		
		/*! Updates the text that shall be displayed. */
		void set_text(const std::string& text, SDL_Renderer* renderer);
		
		/*! Adds the text-texture at specified location to renderer. */
		void draw(const int x, const int y, SDL_Renderer* renderer);
		
		/*! Gets the height of the text. */
		int get_height() const;
		
		/*! Gets the width of the text. */
		int get_width() const;
};

/*! Internal class for handling missing font resources. */
class FontLoadingException : public std::runtime_error
{
	public:
		FontLoadingException(std::string message) :
		runtime_error(message) {}
};

#endif