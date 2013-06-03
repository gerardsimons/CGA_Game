#include "SpaceShip.h"
#include <GL/glut.h>


/*
 * SpaceShip.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

Vec3Df position;
Vec3Df direction;
float speed;

SpaceShip::SpaceShip() {
	// TODO Auto-generated constructor stub

}

SpaceShip::~SpaceShip() {
	// TODO Auto-generated destructor stub
}

void SpaceShip::display(){

	glBegin(GL_QUADS);
		glNormal3d(0, 0, 1);
		glVertex3f(1,1,3);
		glVertex3f(1,0,3);
		glVertex3f(2,0,3);
		glVertex3f(2,1,3);
	glEnd();

}

void SpaceShip::updateX(){

}

void SpaceShip::updateY(){

}
