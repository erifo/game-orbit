#ifndef ORBITAL_H
#define ORBITAL_H

#include <string>
#include "sprite.h"

class Orbital : public Sprite
{
	private:
		int x_center; /*! X position of anchor. */
		int y_center; /*! Y position of anchor. */
		double d_angle; /*! The mount rotated in one frame. */
		double c_angle; /*! Current stage in the rotation. */
		double radius; /*! Distance from anchor to rotating object. */
		
	public:
		Orbital(SDL_Renderer* renderer, std::string filename, int x=0, int y=0);
		virtual ~Orbital() = default;
		
		/*! Changes the speed of rotation and distance from the anchor-point. */
		void set_parameters(double i_radius, double i_speed);
		
		/*! Changes the position of the anchor-point. */
		void set_orbit_mid(int x, int y);
		
		/*! Called each frame. Updates rotation and location. */
		virtual void update();
		
};

#endif