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
#include "AssistentSpaceShip.h"



Bullet::Bullet(float xNew, float yNew, signed int dir) {
	//printf("I'm a weird bullet, created at (%f,%f) \n", x, y );
	x = xNew+(GameSettings::AIRPLANE_SIZE[0]/2);
	y = yNew+(GameSettings::AIRPLANE_SIZE[1]/4);
	direction = dir;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::display(){


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[2]);

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

			if(direction == 1)
			{
				glTexCoord2f(0.0f,0.0f);
				glVertex3f(x,								y+GameSettings::BULLET_SIZE[1],		1.1);
				glTexCoord2f(0.0f,1.0f);
				glVertex3f(x,								y,									1.1);
				glTexCoord2f(1.0f,1.0f);
				glVertex3f(x+GameSettings::BULLET_SIZE[0],	y,									1.1);
				glTexCoord2f(1.0f,0.0f);
				glVertex3f(x+GameSettings::BULLET_SIZE[0],	y+GameSettings::BULLET_SIZE[1],		1.1);
			}
			if(direction == -1)
			{
				glTexCoord2f(1.0f,0.0f);
				glVertex3f(x,								y+GameSettings::BULLET_SIZE[1],		1.1);
				glTexCoord2f(1.0f,1.0f);
				glVertex3f(x,								y,									1.1);
				glTexCoord2f(0.0f,1.0f);
				glVertex3f(x+GameSettings::BULLET_SIZE[0],	y,									1.1);
				glTexCoord2f(0.0f,0.0f);
				glVertex3f(x+GameSettings::BULLET_SIZE[0],	y+GameSettings::BULLET_SIZE[1],		1.1);
			}
		glEnd();

		//reset to previous state
		glPopAttrib();

	glDisable(GL_TEXTURE_2D);

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

bool Bullet::hasCollision( AssistentSpaceShip * ass )
{
	if( x >= ass->getPositionX() && x <= (ass->getPositionX()+GameSettings::ASSISTENT_SIZE[0])
		&&
		(y+GameSettings::BULLET_SIZE[1]) >= ass->getPositionY() && (y+GameSettings::BULLET_SIZE[1]) <= ass->getPositionY()+GameSettings::ASSISTENT_SIZE[1]
	)
	{
		return true;
	}
	else if( x >= ass->getPositionX() && x <= ass->getPositionX()+GameSettings::ASSISTENT_SIZE[0]
		&&
		(y) >= ass->getPositionY() && y <= ass->getPositionY()+GameSettings::ASSISTENT_SIZE[1]
	)
	{
		return true;
	}
	else if( (x+GameSettings::BULLET_SIZE[0]) >= ass->getPositionX() && (x+GameSettings::BULLET_SIZE[0]) <= ass->getPositionX()+GameSettings::ASSISTENT_SIZE[0]
		&&
		y >= ass->getPositionY() && y <= ass->getPositionY()+GameSettings::ASSISTENT_SIZE[1]
	)
	{
		return true;
	}
	else if( (x+GameSettings::BULLET_SIZE[0]) >= ass->getPositionX() && (x+GameSettings::BULLET_SIZE[0]) <= ass->getPositionX()+GameSettings::ASSISTENT_SIZE[0]
		&&
		(y+GameSettings::BULLET_SIZE[1]) >= ass->getPositionY() && (y+GameSettings::BULLET_SIZE[1]) <= ass->getPositionY()+GameSettings::ASSISTENT_SIZE[1]
	)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Bullet::outOfRange()
{
	if( abs(x) > GameSettings::MAX_RANGE  )	{ return true; }
	return false;

}
