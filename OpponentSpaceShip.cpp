/*
 * OpponentSpaceShip.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#include "OpponentSpaceShip.h"
#include "GameSettings.h"
#include <GL/glut.h>

OpponentSpaceShip::OpponentSpaceShip() {
	// TODO Auto-generated constructor stub

}

OpponentSpaceShip::OpponentSpaceShip(float x, float y) {
	printf("-- OpponentSpaceShip \n");
	SpaceShip::position  = Vec3Df(x,y,0.0f);
	SpaceShip::bullitsShot = std::vector<Bullet>();
}

OpponentSpaceShip::~OpponentSpaceShip() {
	// TODO Auto-generated destructor stub
}

void OpponentSpaceShip::display() {

	// get x
	float x = getPositionX();
	// get y
	float y = getPositionY();

	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glColor3f(.0,.0,.5);
	glNormal3d(0, 0, 1);
	glBegin(GL_QUADS);

		glVertex3f(x,									y+GameSettings::AIRPLANE_SIZE[1],		1);
		glVertex3f(x,									y,										1);
		glVertex3f(x+GameSettings::AIRPLANE_SIZE[0],	y,										1);
		glVertex3f(x+GameSettings::AIRPLANE_SIZE[0],	y+GameSettings::AIRPLANE_SIZE[1],		1);

		//glVertex3f(0,1,1);
		//glVertex3f(0,0,1);
		//glVertex3f(1,0,1);
		//glVertex3f(1,1,1);
	glEnd();
	//reset to previous state
	glPopAttrib();


	// render bullets
	for(unsigned int i = 0; i<bullitsShot.size(); i++)
	{
		bullitsShot.at(i).display();
	}

}
