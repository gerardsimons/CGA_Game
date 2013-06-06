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
	health = GameSettings::INIT_HEALTH;
	lock = false;
	position  = Vec3Df(x,y,0.0f);
	bullitsShot = new std::vector<Bullet>();
	assSpaceShip = AssistentSpaceShip(
							x+(GameSettings::AIRPLANE_SIZE[0]/2),
							y+(GameSettings::AIRPLANE_SIZE[1]/2),
							0
							);
}

SpaceShip::~SpaceShip() {
	// TODO Auto-generated destructor stub
	//bullitsShot = null;
}

void SpaceShip::display(){

	// get x,y
	float x = getPositionX();
	// get y
	float y = getPositionY();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[0]);

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
		//printf("- render bullet \n");
		bullitsShot->at(i).display();
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

std::vector<Bullet> * SpaceShip::getBulletList()
{
	return bullitsShot;
}

void SpaceShip::removeBullet( int index )
{
	//printf( "removebullet: %f", bullitsShot.at(index).getPositionX() );
	bullitsShot->erase( bullitsShot->begin() + index );
}

void SpaceShip::shoot(){

	printf("is locked ? %i", lock);
	if(!lock)
	{
		Bullet b = Bullet(getPositionX(), getPositionY() , 1);
		bullitsShot->push_back( b );
	}

}

bool SpaceShip::hasCollision( SpaceShip s )
{
	// get x,y
	float x = getPositionX();
	float y = getPositionY();

	if( x >= s.getPositionX() && x <= (s.getPositionX()+GameSettings::AIRPLANE_SIZE[0])
		&&
		(y+GameSettings::AIRPLANE_SIZE[1]) >= s.getPositionY() && (y+GameSettings::AIRPLANE_SIZE[1]) <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
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
	else if( (x+GameSettings::AIRPLANE_SIZE[0]) >= s.getPositionX() && (x+GameSettings::AIRPLANE_SIZE[0]) <= s.getPositionX()+GameSettings::AIRPLANE_SIZE[0]
		&&
		y >= s.getPositionY() && y <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
	)
	{
		return true;
	}
	else if( (x+GameSettings::AIRPLANE_SIZE[0]) >= s.getPositionX() && (x+GameSettings::AIRPLANE_SIZE[0]) <= s.getPositionX()+GameSettings::AIRPLANE_SIZE[0]
		&&
		(y+GameSettings::AIRPLANE_SIZE[1]) >= s.getPositionY() && (y+GameSettings::AIRPLANE_SIZE[1]) <= s.getPositionY()+GameSettings::AIRPLANE_SIZE[1]
	)
	{
		return true;
	}
	else
	{
		return false;
	}

}

AssistentSpaceShip * SpaceShip::getAssistent()
{
	return &(assSpaceShip);
}

void SpaceShip::decreaseHealth()
{

	health--;
	printf("CURRENT HEALTH: %f\n", health);
	if (health <= 0)
		printf("GAME OVER\n");	// todo game over handling
}

void SpaceShip::setBulletLock( bool l )
{
	lock = l;
}

bool SpaceShip::getBulletLock()
{
	return lock;
}
