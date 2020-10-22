#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <string>
#include <vector>
#include "spike.h"
#include "projectile.h"

class Launcher : public Spike
{
	private:
		std::vector<Spike*>& new_spikes;
		char direction; /*! Character saving direction.*/ 
		int exit_point_x; /*! Sets x position for projectile */
		int exit_point_y; /*! Sets y position for projectile */
		SDL_Renderer* renderer;
		int timer; /*! Sets timer for spike */
		int const timer_max; /*! Sets constant maximum time for timer. */

	public:
		Launcher(SDL_Renderer* renderer, std::vector<Spike*>& new_spikes, std::string filename, char dir='u', int x=0, int y=0);
		~Launcher() = default;
		Launcher(Launcher const& rhs) = default;
		Launcher& operator=(Launcher const& rhs) = default;
		void update() override;
		Projectile* create_projectile();
		void set_exit_point();
		void draw(SDL_Renderer* renderer) override;
		void reset();
};

#endif