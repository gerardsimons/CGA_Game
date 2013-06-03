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

#include <GL/glut.h>


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
	std::vector<GLuint> Texture;

public:
	SpaceShip();
	SpaceShip(float x, float y);
	virtual ~SpaceShip();
	virtual void display();
	void updateX(float x);
	void updateY(float y);
	float getPositionX();
	float getPositionY();
	Vec3Df getPosition();

	std::vector<Bullet> getBulletList();

	void removeBullet( int index );

	void shoot();
};

#endif /* SPACESHIP_H */
