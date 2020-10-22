#ifndef VICTORY_H
#define VICTORY_H

#include <string>
#include "sprite.h"
#include "text.h"

class Victory  : public Sprite
{
    private:
        Sprite* retry_button; /*! Button to restart the current level. */
        Sprite* next_button; /*! Button to proceed to the next level. */
        Text* time; /*! The best time recorded for the current level. */
        Text* best_time_title; /*! Descriptive text for the best time. */
        bool enabled; /*! Determines if victory screen should be rendered. */

    public:
        Victory(SDL_Renderer* renderer, std::string filename);
        ~Victory();
		Victory(Victory const& rhs) = default;
		Victory& operator=(Victory const& rhs) = default;
		
		/*! Adds victory screen to specified renderer. */
        void draw(SDL_Renderer* renderer);
        
        /*! Sets the enabled state of the victory screen. */
        void set_enabled(bool const& state);
        
        /*! Checks if victory screen is enabled. */
        bool is_enabled();
        
        /*! Gets the next-button. */
        Sprite* get_next_button();
        
        /*! Gets the retry-button */
        Sprite* get_retry_button();
        
        /*! Gets the text object so it can be changed from the outside. */
        Text* get_text_object();
};

#endif