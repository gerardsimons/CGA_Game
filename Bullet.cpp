/*
 * Bullet.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#include "Bullet.h"
#include "GameSettings.h"
#include <GL/glut.h>
#include "SpaceShip.h"

Bullet::Bullet(){

}

Bullet::Bullet(float xNew, float yNew) {
	printf("I'm a weird bullet, created at (%f,%f)", x, y );
	x = xNew;
	y = yNew;

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::display(){

		// TODO: in main
		x = getPositionX() + GameSettings::BULLET_SPEED;
		//printf("x: %f", x);

		//remember all states of the GPU
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(1,1,0);
		glNormal3d(0, 0, 1);
		glBegin(GL_QUADS);

			glVertex3f(x,								y+GameSettings::BULLET_SIZE[1],		0.9);
			glVertex3f(x,								y,									0.9);
			glVertex3f(x+GameSettings::BULLET_SIZE[0],	y,									0.9);
			glVertex3f(x+GameSettings::BULLET_SIZE[0],	y+GameSettings::BULLET_SIZE[1],		0.9);

		glEnd();

		//reset to previous state
		glPopAttrib();

}

float Bullet::getPositionX(){
	return x;
}

float Bullet::getPositionY(){
	return y;
}

void Bullet::updateX(float xNew){
	x = xNew;
}

void Bullet::updateY(float yNew){
	y = yNew;
}

bool Bullet::hasCollision( SpaceShip s )
{
	if( x >= s.getPositionX() && x <= (s.getPositionX()+GameSettings::AIRPLANE_SIZE[0])
		&&
		(y+GameSettings::BULLET_SIZE[1]) >= s.getPositionY() && (y+GameSettings::BULLET_SIZE[1]) <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
	)
	{
		return true;
	}
	else if( x >= s.getPositionX() && x <= s.getPositionX()+GameSettings::AIRPLANE_SIZE[0]
		&&
		(y) >= s.getPositionY() && y <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
	)
	{
		return true;
	}
	else if( (x+GameSettings::BULLET_SIZE[0]) >= s.getPositionX() && (x+GameSettings::BULLET_SIZE[0]) <= s.getPositionX()+GameSettings::AIRPLANE_SIZE[0]
		&&
		y >= s.getPositionY() && y <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
	)
	{
		return true;
	}
	else if( (x+GameSettings::BULLET_SIZE[0]) >= s.getPositionX() && (x+GameSettings::BULLET_SIZE[0]) <= s.getPositionX()+GameSettings::AIRPLANE_SIZE[0]
		&&
		(y+GameSettings::BULLET_SIZE[1]) >= s.getPositionY() && (y+GameSettings::BULLET_SIZE[1]) <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
	)
	{
		return true;
	}
	else
	{
		return false;
	}

}
