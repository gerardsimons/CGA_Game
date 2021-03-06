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
#include "AssistentSpaceShip.h"
#include "Model.h"

class SpaceShip;
//class AssistentSpaceShip;

class Bullet {
private:
	float x;
	float y;
	signed int direction;
public:
	Bullet();
	Bullet(float x, float y, signed int dir);
	virtual ~Bullet();
	void display();
	void updateX(float x);
	void updateY(float y);
	float getPositionX();
	float getPositionY();

	bool hasCollision( SpaceShip s );
	bool hasCollision( AssistentSpaceShip * ass );
	bool hasCollision( Model * boss );

	bool outOfRange();
};

#endif /* BULLET_H_ */
