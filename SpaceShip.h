#ifndef SPACESHIP_H
#define SPACESHIP_H

#ifdef WIN32
#include <Windows.h>
#endif

#include <stdlib.h>

#include "stdio.h"
#include <vector>
#include "Vec3D.h"
#include "Bullet.h"


/* SpaceShip.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */


class SpaceShip {
protected:
	Vec3Df position;
	float direction;
	float speed;
	std::vector<Bullet> bullitsShot;

public:
	SpaceShip();
	SpaceShip(float x, float y);
	virtual ~SpaceShip();
	void display();
	void updateX(float x);
	void updateY(float y);
	float getPositionX();
	float getPositionY();
	Vec3Df getPosition();

	void shoot();
};

#endif /* SPACESHIP_H */
