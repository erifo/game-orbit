#include <iostream>
#include <fstream>
#include <sstream>
#include "map.h"

using namespace std;

Map::Map(SDL_Renderer* renderer, std::string filename)
	:   texture_file{},
		won{false}, spikes{}, new_spikes{},
		stopwatch{new Stopwatch("00:00", renderer)},
		title{}, tileset{}, background{},
		victory_screen{new Victory(renderer, "./img/victory_screen.png")},
		highscore{new Highscore()}, renderer{renderer},
		start_circle{new Sprite(renderer, "./img/start.png")},
		bubble{new Bubble(renderer, "./img/bubble.png")},
		goal{new Goal(renderer, "./img/goal.png")}
{
	load(renderer, filename);
}

Map::~Map()
{
	delete stopwatch;
	delete title;
	SDL_DestroyTexture(background);
	delete victory_screen;
	delete highscore;
	delete start_circle;
	delete bubble;
	delete goal;

	for (std::vector<Spike*>::iterator spike = spikes.begin();
			spike != spikes.end();
			++spike)
	{
		delete (*spike);
		spike = spikes.erase(spike);
		--spike;
	}
}

//Generalized function for creating launchers in a chosen direction.
void Map::create_launcher(SDL_Renderer* renderer,
						std::string filename,
						int x, int y, char dir,
						int const TILE_SIZE)
{
	Launcher* launcher = new Launcher(renderer, new_spikes, filename, dir);
	launcher->set_x(x * TILE_SIZE);
	launcher->set_y(y * TILE_SIZE);
	launcher->set_exit_point();
	spikes.push_back(launcher);
	launcher = nullptr;
}

void Map::load(SDL_Renderer* renderer, std::string filename)
{
	//Open the level text file.
	ifstream map(filename);

	if( map == NULL )
	{
		cout << "Map got rekt" << endl;
	}
	else
	{
		const char TILE_CLUSTER = '#';
		const char TILE_LAUNCHER_UP = 'A';
		const char TILE_LAUNCHER_DOWN = 'V';
		const char TILE_LAUNCHER_RIGHT = '>';
		const char TILE_LAUNCHER_LEFT = '<';
		const char TILE_BUBBLE_START = 'o';
		const char TILE_BUBBLE_GOAL = '@';
		const int TILE_SIZE = 60;

		std::string line;
		int y{0};
		while (getline(map, line)) // Y
		{
			if (y == 0) // Loads information from the first line.
			{
				vector<std::string> lvl_info{};
				std::string section;
				stringstream ss(line);

				while (getline(ss, section, '|'))
				{ lvl_info.push_back(section); }

				if (lvl_info.size() < 2)
				{
					tileset = "./img/tilesets/jungle";

					if (lvl_info.size() < 1)
					{ title = new Text("DEFAULT TEXT", renderer); }
					else
					{ title = new Text((lvl_info.at(0)), renderer); }
				}
				else
				{
					tileset = "./img/tilesets/" + lvl_info.at(1);
					title = new Text((lvl_info.at(0)), renderer);
				}
			}
			else //Loads level design from the remaining lines.
			{
				for (uint x{0}; x < line.length(); ++x) // X
				{
					if (line.at(x) == TILE_CLUSTER)
					{
						Cluster* cluster = new Cluster(renderer, tileset + "/cluster.png");
						cluster->set_x(x * TILE_SIZE);
						cluster->set_y(y * TILE_SIZE);
						spikes.push_back(cluster);
						cluster = nullptr;
					}
					else if (line.at(x) == TILE_LAUNCHER_UP)
					{
						create_launcher(renderer, tileset + "/launcher.png", x, y, 'u', TILE_SIZE);
					}
					else if (line.at(x) == TILE_LAUNCHER_DOWN)
					{
						create_launcher(renderer, tileset + "/launcher.png", x, y, 'd', TILE_SIZE);
					}
					else if (line.at(x) == TILE_LAUNCHER_RIGHT)
					{
						create_launcher(renderer, tileset + "/launcher.png", x, y, 'r', TILE_SIZE);
					}
					else if (line.at(x) == TILE_LAUNCHER_LEFT)
					{
						create_launcher(renderer, tileset + "/launcher.png", x, y, 'l', TILE_SIZE);
					}
					else if (line.at(x) == TILE_BUBBLE_START)
					{
						//Bubble
						bubble->set_x_resting(x * TILE_SIZE + (TILE_SIZE/2));
						bubble->set_y_resting(y * TILE_SIZE + (TILE_SIZE/2));
						bubble->set_parameters(50, 0.025); //0.05?

						//Starting Circle
						start_circle->set_x_mid(x * TILE_SIZE + (TILE_SIZE/2));
						start_circle->set_y_mid(y * TILE_SIZE + (TILE_SIZE/2));

					}
					else if (line.at(x) == TILE_BUBBLE_GOAL)
					{
						goal->set_x(x * TILE_SIZE);
						goal->set_y(y * TILE_SIZE);
					}
				}
			}
			++y;
		}

		//Background
		SDL_Surface* temp_bg_surf = IMG_Load((tileset + "/background.png").c_str());
		background = SDL_CreateTextureFromSurface(renderer, temp_bg_surf);
		SDL_FreeSurface(temp_bg_surf);
	}
}

void Map::start()
{
	bubble->set_resting(false);
	stopwatch->start();
}

void Map::remove_projectiles(std::vector<Spike*>& spike_vector)
{
	for (std::vector<Spike*>::iterator spike_it = spike_vector.begin();
			spike_it != spike_vector.end();
			++spike_it)
	{
		Projectile* projectile = dynamic_cast<Projectile*>((*spike_it));

		if (projectile != nullptr)
		{
			(*spike_it)->delete_me = true;
		}
	}
}

void Map::reset()
{
	bubble->set_resting(true);
	stopwatch->stop();
	stopwatch->set_text("hej", renderer);
	remove_projectiles(spikes);
	remove_projectiles(new_spikes);

	for (Spike* spike : spikes)
	{
		Launcher* launcher = dynamic_cast<Launcher*>(spike);

		if (launcher != nullptr)
		{
			launcher->reset();
		}
	}
}

void Map::update()
{
	if (victory_screen->is_enabled())
	{
		//Update victory screen.
	}
	else
	{
		//Update Bubble
		bubble->update();

		//Update Stopwatch
		if (stopwatch->is_running())
		{
			stopwatch->update();
		}

		//Check all collision related to spikes.
		for (std::vector<Spike*>::iterator spikeA = spikes.begin();
				spikeA != spikes.end();
				++spikeA)
		{
			(*spikeA)->update();
			if (!(bubble->is_god()) && (*spikeA)->intersects_with_circle(bubble))
			{
				reset();
			}

			//Handles projectile-cluster collision.
			for (Spike* spikeB : spikes)
			{
				if ( (spikeB->delete_me == true) )
				{ continue; }

				Projectile* projectile = dynamic_cast<Projectile*>((*spikeA));
				Cluster* cluster = dynamic_cast<Cluster*>(spikeB); //For comparison.
				Launcher* launcher = dynamic_cast<Launcher*>(spikeB); //For comparison.

				if ((projectile != nullptr)
					&& (cluster != nullptr || launcher != nullptr)
					&& ((*spikeA) != spikeB))
				{
					if ((*spikeA)->intersects_with_rect(spikeB))
					{
						//cout << (*spikeA)->get_name() << spikeB->get_name() << endl;
						//Removes spike from vector
						(*spikeA)->delete_me = true;
					}
				}
			}
		}
	}

	//Add new spikes.
	for (Spike* new_spike : new_spikes)
	{
		spikes.push_back(new_spike);
	}
	new_spikes.clear();

	//Delete unwanted spikes.
	for (std::vector<Spike*>::iterator spike = spikes.begin();
			spike != spikes.end();
			++spike)
	{
		if ( (*spike)->delete_me )
		{
			delete (*spike);
			spike = spikes.erase(spike);
			--spike;
		}
	}

	//Detect collision between bubble and goal.
	if (bubble->intersects_with_circle(goal))
	{
		highscore->set_filename("./highscore.txt");
		highscore->set_level_name(title->text);
		highscore->save_highscore(stopwatch->get_time());
		highscore->load_highscore();

		std::string score{to_string(highscore->get_highscore())};
		victory_screen->get_text_object()->set_text(score + "sec", renderer);

		reset();

		victory_screen->set_enabled(true);
	}
}

//Call the draw() function of all relevant objects.
void Map::draw(SDL_Renderer* renderer)
{
	//Render background.
	SDL_RenderCopy(renderer, background, nullptr, nullptr);

	//Render goal.
	if (goal->is_enabled())
	{ goal->draw(renderer); }

	if (start_circle->is_enabled())
	{ start_circle->draw(renderer); }

	//Render all spikes.
	for (Spike* spike : spikes)
	{
		spike->draw(renderer);
	}

	//Render bubble.
	if (bubble->is_enabled())
	{ bubble->draw(renderer); }



	//Update and Render Stopwatch.
	stopwatch->set_text("Time: " + std::to_string(stopwatch->get_time()), renderer);
	stopwatch->draw(1150-stopwatch->get_width(), 0, renderer);

	//Render title.
	if (title != nullptr)
	{
		title->draw(0, 0, renderer);
	}
	else
	{ std::cout << "Failed to render title" << std::endl; }

	if (victory_screen->is_enabled())
	{
		victory_screen->draw(renderer);
	}
}

Victory* Map::get_victory_screen()
{
	return victory_screen;
}

bool Map::has_won()
{
	return won;
}

void Map::set_won(bool state)
{
	won = state;
}