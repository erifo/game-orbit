#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <string>
#include <time.h>
#include "text.h"

class Stopwatch : public Text
{
	private:
		time_t origin_t; /*! The moment the stopwatch starts. */
		time_t current_t; /*! The current moment. */
		int delta_t; /*! The diff. in seconds between current_t & origin_t */
		bool running; /*! Decides if delta_t should update or not. */

	public:
		Stopwatch(std::string text, SDL_Renderer* renderer);
		
		/*! Initiates the timer. */
		void start();
		
		/*! Stops the timer. */
		void stop();
		
		/*! Calculates delta_t */
		void update();
		
		/*! Checks if the stopwatch is running. */
		bool is_running();
		
		/*! Gets the elapsed time in seconds. */
		int get_time();
};

#endif