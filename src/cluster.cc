#include "cluster.h"

Cluster::Cluster(SDL_Renderer* renderer, std::string filename, int x, int y)
	: Spike(renderer, filename, x, y)

/*! Gives the Cluster a name to make it easier for troubleshooting, a width and a height.*/
{
	name = "cluster";   /*! A string containing name of the variable.*/
	set_w(60);          /*! A int value for the width.*/
	set_h(60);          /*! A int value for the height.*/
}