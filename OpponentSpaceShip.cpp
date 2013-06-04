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
	SpaceShip::bullitsShot = new std::vector<Bullet>();
}

OpponentSpaceShip::~OpponentSpaceShip() {
	// TODO Auto-generated destructor stub
}

void OpponentSpaceShip::display() {

	// get x,y
	float x = getPositionX();
	float y = getPositionY();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[1]);

		//remember all states of the GPU
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(1,1,1);
		glNormal3d(0, 0, 1);

		// texture addition
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(x,									y+GameSettings::AIRPLANE_SIZE[1],		1);
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(x,									y,										1);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(x+GameSettings::AIRPLANE_SIZE[0],	y,										1);
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(x+GameSettings::AIRPLANE_SIZE[0],	y+GameSettings::AIRPLANE_SIZE[1],		1);

		glEnd();
		//reset to previous state
		glPopAttrib();

	glDisable(GL_TEXTURE_2D);

	// render bullets
	for(unsigned int i = 0; i<bullitsShot->size(); i++)
	{
		bullitsShot->at(i).display();
	}

}

void OpponentSpaceShip::shoot(){
	Bullet b = Bullet(getPositionX(), getPositionY());
	SpaceShip::bullitsShot->push_back( b );
	//printf("I have shot %d times \n", bullitsShot.size());

}
