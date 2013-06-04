/*
 * Bullet.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#ifndef BULLET_H_
#define BULLET_H_

#ifdef WIN32
#include <Windows.h>
#endif
#include <stdlib.h>
#include "stdio.h"
#include "Vec3D.h"

class SpaceShip;

class Bullet {
private:
	float x;
	float y;
public:
	Bullet();
	Bullet(float x, float y);
	virtual ~Bullet();
	void display();
	void updateX(float x);
	void updateY(float y);
	float getPositionX();
	float getPositionY();

	bool hasCollision( SpaceShip s );

	bool outOfRange();
};

#endif /* BULLET_H_ */
