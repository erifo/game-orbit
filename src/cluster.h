#ifndef CLUSTER_H
#define CLUSTER_H

#include <string>
#include "spike.h"
/*! Inherits from the Spike class.*/
class Cluster : public Spike
{
	public:
	/*! Public constructor for the cluster class. */
		Cluster(SDL_Renderer* renderer, std::string filename, int x=0, int y=0);
};

#endif