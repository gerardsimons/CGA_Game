#ifndef SPACESHIP_H
#define SPACESHIP_H

#ifdef WIN32
#include <Windows.h>
#endif


#include "stdio.h"
#include "Vec3D.h"


/* SpaceShip.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */


class SpaceShip {
private:
	Vec3Df position;
	Vec3Df direction;
	float speed;
	//std::vector<Bullet> bullitsShot;

public:
	SpaceShip();
	virtual ~SpaceShip();
	void display();
	void updateX();
	void updateY();
};

#endif /* SPACESHIP_H */
