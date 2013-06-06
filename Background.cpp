/*
 * Background.cpp
 *
 *  Created on: Jun 6, 2013
 *      Author: gerard
 */

#include "Background.h"


Background::Background(int x, int y, int z, int width, int height) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->width = width;
	this->height = height;
}

void Background::draw()
{
	glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[5]);
	printf("drawing background...\n");
	//remember all states of the GPU
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glNormal3d(0, 0, -1);
	glEnable(GL_TEXTURE_2D);

	// texture addition
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);

	glBegin(GL_QUADS);
		glColor3f(1,1,1);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(x,y,z);
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(x,y+height,z);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(x+width,y+height,z);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(x+width,y,z);
	glEnd();
	//reset to previous state
	glPopAttrib();


	glDisable(GL_TEXTURE_2D);
}

Background::~Background() {
	// TODO Auto-generated destructor stub
}

