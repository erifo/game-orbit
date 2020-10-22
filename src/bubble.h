#ifndef BUBBLE_H
#define BUBBLE_H

#include <string>
#include "orbital.h"
/*! Inheritates from public functions of the Orbital class. */
class Bubble : public Orbital
{
	private:
	/*! Private variables. 
	    Contains datatypes.
	*/
		int x_resting;
		int y_resting;
		bool resting;
		bool godmode;

	public:
	/*! Public function variables. 
	    Constructor for bubble and getters and setters for bubble class. 
	*/
		Bubble(SDL_Renderer* renderer, std::string filename, int x=0, int y=0);
		void update() override;

	/*! Setters. 
	*/
		void set_x_resting(int x);
		void set_y_resting(int y);
		void set_resting(bool state);
		void set_god(bool state);

	/*! Getters.
	*/
		int get_x_resting() const;
		int get_y_resting() const;
		bool is_resting() const;
		bool is_god() const;
};

#endif