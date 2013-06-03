/*
 * Bullet.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#include "Bullet.h"
#include "GameSettings.h"
#include <GL/glut.h>

Bullet::Bullet(float x, float y) {
	printf("I'm a weird bullet, created at (%f,%f)", x, y );
	position  = Vec3Df(x,y,0.0f);

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::display(){

		updateX(getPositionX()+ .02);

		// get x
		float x = getPositionX();
		// get y
		float y = getPositionY();

		//remember all states of the GPU
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(1,1,0);
		glNormal3d(0, 0, 1);
		glBegin(GL_QUADS);

		glVertex3f(x,								y+GameSettings::BULLET_SIZE[1],		0.9);
		glVertex3f(x,								y,										0.9);
		glVertex3f(x+GameSettings::BULLET_SIZE[0],	y,										0.9);
		glVertex3f(x+GameSettings::BULLET_SIZE[0],	y+GameSettings::BULLET_SIZE[1],		0.9);

			//glVertex3f(0,1,1);
			//glVertex3f(0,0,1);
			//glVertex3f(1,0,1);
			//glVertex3f(1,1,1);
		glEnd();

		//reset to previous state
		glPopAttrib();

}

float Bullet::getPositionX(){
	return position[0];
}

float Bullet::getPositionY(){
	return position[1];
}

void Bullet::updateX(float x){
	position[0] = x;
}

void Bullet::updateY(float y){
	position[1] = y;
}
