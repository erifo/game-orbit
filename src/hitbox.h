#ifndef HITBOX_H
#define HITBOX_H

#include <SDL2/SDL.h>

class Hitbox
{
	private:
		SDL_Rect rect;
		int radius = 0;

	public:
		/*! Constructor */
		Hitbox();
		virtual ~Hitbox() = default;
		Hitbox(int x, int y, int w, int h);
		
		/*! Intersection */
		bool intersects_with_rect(Hitbox* const& b) const;  /*! Checks if a object intersects with a rectangular object */
		bool intersects_with_circle(Hitbox* const& b) const; /*! Checks if a object intersects with a circular object */
		bool intersects_with_point(int const& x, int const& y) const; /*! Checks collision with cursor. */

		/*! Setters */
		void set_x(int x);  /*! x-position of object's hitbox. */
		void set_y(int y);  /*! x-position of object's hitbox. */
		void set_w(int w);  /*! width of object's hitbox. */
		void set_h(int h);  /*! height of object's hitbox. */
		void set_x_mid(int x);  /*! middle of circle's hitbox in x axis. */
		void set_y_mid(int y);  /*! middle of circle's hitbox in y axis. */

		/*!Getters */
		SDL_Rect get_rect() const;
		int get_x() const; /*! Get x. */
		int get_y() const; /*! Get y. */
		int get_w() const; /*! Get width. */
		int get_h() const; /*! Get height. */
		int get_x_mid() const; /*! Get middle in of circle in x axis. */
		int get_y_mid() const; /*! Get middle in of circle in y axis. */
};

#endif