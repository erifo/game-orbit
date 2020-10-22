#include "game.h"

using namespace std;

Game::Game() : levels{} {}

//Returns a vector of filenames in a specified directory.
vector<string> Game::open(string path = ".")
{
    DIR* dir{};
    dirent* pdir{};
    vector<string> files{};
    dir = opendir(path.c_str());
    while (true)
	{
        pdir = readdir(dir);
        if (!pdir) { break; }
        files.push_back(pdir->d_name);
	}
    closedir(dir);
    return files;
}

//Loads the numbered levels using "dirent.h".
void Game::load_all_levels(SDL_Renderer* renderer)
{
    vector<string> level_files = open("./lvls");
    sort(level_files.begin(), level_files.end());
	for (string level : level_files)
	{
		if (level.substr(0,3) == "lvl")
		{
            levels.push_back(new Map(renderer, "./lvls/"+level));
            cout << "Loaded Level: " << level << endl;
		}
	}
}


//--- Main Program ---
int Game::run()
{
    //Error handle base SDL.
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Video is poof" << endl;
		exit(1);
	}

    //Error handle PNG display.
    if ( !( IMG_Init ( IMG_INIT_PNG ) | IMG_INIT_PNG ) )
	{
		cout << "Pencil is break." << endl;
	}
	cout << "SDL2 is initiated." << endl;

    //Error handle the font used.
	if(TTF_Init() == -1)
	{
    	cerr << "Letters are bonk." << endl;
    	exit(2);
	}

    //Initiate Window and Renderer.
	SDL_Window* window = SDL_CreateWindow("TDP005: Orbit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    //Loading all the levels.
    //levels.push_back(new Map(renderer, "./lvls/lvl11.orbit"));
    load_all_levels(renderer);

	//Framerate handling
	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;

	//--- Main Game Loop ---
	bool running{true};
	for (Map* level : levels)
	{
		while (!level->has_won() == true)
		{
			//Framerate updating.
			Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
			lastFrameTime += frameDelay;

			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
                //Quit request.
                if (event.type == SDL_QUIT)
				{
					cout << "Game is ending." << endl;
					running = false;
					break;
				}

                //Moving the cursor.
				if (event.type == SDL_MOUSEMOTION)
				{
					level->bubble->set_orbit_mid(event.motion.x, event.motion.y);
				}

                //Clicking on various things.
                if (event.type == SDL_MOUSEBUTTONUP)
				{
					if (level->bubble->intersects_with_point(event.motion.x, event.motion.y))
					{
						level->start();
					}
                    else if (level->get_victory_screen()->is_enabled() && level->get_victory_screen()->get_retry_button()->intersects_with_point(event.motion.x, event.motion.y))
					{
                        level->get_victory_screen()->set_enabled(false);
                        level->reset();
					}
                    else if (level->get_victory_screen()->is_enabled() && level->get_victory_screen()->get_next_button()->intersects_with_point(event.motion.x, event.motion.y))
					{
						level->set_won(true);
					}
				}

                //Turns Godmode on and off.
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_LEFT])
                {
                    if (!level->bubble->is_god())
                    {
                        cout << "GOD" << endl;
                        level->bubble->set_god(true);
                    }
                }
                else
                {
                    if (level->bubble->is_god())
                    {
                        cout << "MORTAL" << endl;
                        level->bubble->set_god(false);
                    }
                }
			}

			//Update and Draw Screen.
			SDL_RenderClear(renderer);
			level->update();
			level->draw(renderer);
			SDL_RenderPresent(renderer);

			//Wait before drawing the next frame
			frameDelay = SDL_GetTicks() - lastFrameTime;
			if (targetFrameDelay > frameDelay)
			{
				Uint32 sleepTime = targetFrameDelay - frameDelay;
				SDL_Delay(sleepTime);
			}
			if (!running) {break;}
		}
		if (!running) {break;}
	}

	//--- End Game Cleanup ---
    for (Map* level : levels)
    {
        delete level;
    }
    levels.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	cout << "Have a nice day." << endl;
	return 0;
}