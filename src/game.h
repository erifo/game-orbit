#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <dirent.h>
#include "map.h"

using namespace std;

class Game
{
    private:
        const int SCREEN_WIDTH{1200};  /*! Sets the screen width of the game to a const width. */
        const int SCREEN_HEIGHT{720};  /*! Sets the screen height of the game to a const height. */
        vector<Map*> levels;            /*! Stores the levels */

    public:
        Game();         /*! Constructor for game. */
        ~Game() = default;  /*! Destructor for game. */
        Game(Game const& rhs) = default;    /*! Copy levels from one game to another. Not used. */
		Game& operator=(Game const& rhs) = default; /*! Not used. */

        vector<string> open(string path);   /*! Returns a vector of filenames in a specified directory. */
        void load_all_levels(SDL_Renderer* renderer); /*! Loads all the levels. */
        int run();      /*! Runs the game. Return 1, 2 or NULL. */
};

#endif