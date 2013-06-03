#include "SpaceShip.h"
#include "GameSettings.h"

#include "loadppm.h"



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

	Texture.resize(3);
	Texture[0]=0;
	Texture[1]=0;
	Texture[2]=0;

	PPMImage image("spaceShip.PPM");
	glGenTextures(1, &Texture[0]);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.sizeX, image.sizeY,
		GL_RGB, GL_UNSIGNED_BYTE, image.data);
	glBindTexture(GL_TEXTURE_2D, 0);

}

SpaceShip::~SpaceShip() {
	// TODO Auto-generated destructor stub
}

void SpaceShip::display(){

	// get x,y
	float x = getPositionX();
	float y = getPositionY();




	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Texture[0]);




		//remember all states of the GPU
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glColor3f(1,1,1);
		glNormal3d(0, 0, 1);

		// texture addition
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_NEAREST);


		glBegin(GL_QUADS);

			glTexCoord2f(0.0f,1.0f);
			glVertex3f(x,									y+GameSettings::AIRPLANE_SIZE[1],		1);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(x,									y,										1);
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(x+GameSettings::AIRPLANE_SIZE[0],	y,										1);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(x+GameSettings::AIRPLANE_SIZE[0],	y+GameSettings::AIRPLANE_SIZE[1],		1);

		glEnd();
		//reset to previous state
		glPopAttrib();

	glBindTexture(GL_TEXTURE_2D,1);
	glDisable(GL_TEXTURE_2D);

	// render bullets
	for(unsigned int i = 0; i<bullitsShot.size(); i++)
	{
		//printf("- render bullet \n");
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

std::vector<Bullet> SpaceShip::getBulletList()
{
	return bullitsShot;
}

void SpaceShip::removeBullet( int index )
{
	//printf( "removebullet: %f", bullitsShot.at(index).getPositionX() );
	bullitsShot.erase( bullitsShot.begin() + index );
}

void SpaceShip::shoot(){
	Bullet b = Bullet(getPositionX(), getPositionY());
	bullitsShot.push_back( b );
	//printf("I have shot %d times \n", bullitsShot.size());

}
