#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "bubble.h"
#include "cluster.h"
#include "launcher.h"
#include "goal.h"
#include "stopwatch.h"
#include "text.h"
#include "victory.h"
#include "highscore.h"

class Map
{
	private:
		std::string texture_file; /*! Texture file to be read. */
		bool won;                   /*! Check if the level has been won. */
		std::vector<Spike*> spikes; /*! Contains the spikes. */
		std::vector<Spike*> new_spikes; /*! Contains the new spikes created. */
		Stopwatch* stopwatch;   /*! Contains stopwatch. Keeps track of elapsed time. */
		Text* title;            /*! Contains the stored level title from specifified level. */
		std::string tileset;    /*! Contains the tileset for specified level. */
		SDL_Texture* background; /*! Stores the background texture. */
		Victory* victory_screen; /*! Contains victoryscreen. Victory screen is displayed after level been won. */
		void remove_projectiles(std::vector<Spike*>& spikes); /*! Destroy projectiles after collision with object. */
		Highscore* highscore;   /*! Contains Highscore. Updates the time Highscore. */
		SDL_Renderer* renderer; /*! Used to create sprites and instances of other classes. */
		Sprite* start_circle;   /*! Contains the start circle sprite. */

	public:
		Map(SDL_Renderer* renderer, std::string filename);
		~Map();
		Map(Map const& rhs) = default;
		Map& operator=(Map const& rhs) = default;
		Bubble* bubble;     /*! Contains the bubble sprite. */
		Goal* goal;         /*! Contains the goal sprite. */
		
		/*! Creates launcher from given file
		gives it a postition (x, y), 
		a direction from character. 
		The TILE_SIZE is a constant for all tiles.*/
		void create_launcher(SDL_Renderer* renderer,
								std::string filename,
								int x, int y, char dir,
								int const TILE_SIZE);
		void load(SDL_Renderer* renderer, std::string filename);  /*! Load level file. */
		void start();       /*! Starts the level.  */
		void reset();       /*! Resets level from Reset button. */
		void update();      /*! Updates the positions of objects. */
		void draw(SDL_Renderer* renderer);  /*! Draws the relevant objects stored to the specific level.  */
		bool has_won();     /*! Get won. */
		void set_won(bool state); /*! Set won. */
		Victory* get_victory_screen();  /*! Get the victory screen. */

};

#endif