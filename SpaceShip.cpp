#include "SpaceShip.h"
#include "GameSettings.h"
#include <GL/glut.h>


/*
 * SpaceShip.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

SpaceShip::SpaceShip(){}

SpaceShip::SpaceShip(float x, float y) {
	printf("Hi, I'm a weird SpaceShip \n");
	position  = Vec3Df(x,y,0.0f);
	bullitsShot = std::vector<Bullet>();
}

SpaceShip::~SpaceShip() {
	// TODO Auto-generated destructor stub
}

void SpaceShip::display(){

	printf("drawing plane \n");

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

float SpaceShip::getPositionX(){
	return position[0];
}

float SpaceShip::getPositionY(){
	return position[1];
}

Vec3Df SpaceShip::getPosition(){
	return position;
}

void SpaceShip::updateX(float x){
	position[0] = x;
}

void SpaceShip::updateY(float y){
	position[1] = y;
}


void SpaceShip::shoot(){
	Bullet b = Bullet(getPositionX(), getPositionY());
	bullitsShot.push_back( b );
	printf("I have shoot %d times \n", bullitsShot.size());

}
