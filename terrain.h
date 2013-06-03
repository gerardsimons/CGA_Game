#ifndef TERRAIN_H
#define TERRAIN_H

#ifdef WIN32
#include <Windows.h>
#endif

#include <stdlib.h>
#include "stdio.h"
#include "Vec3D.h"
#include <vector>


/* SpaceShip.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */


class Terrain {
private:
	std::vector<float> SurfaceVertices3f;

public:
	Terrain(int,int,float);
	virtual ~Terrain();
	void display();
};

#endif /* TERRAIN_H */
