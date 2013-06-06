/*
 * AssistentSpaceShip.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: nathanmol
 */

#include "AssistentSpaceShip.h"
#include "GameSettings.h"
#include <GL/glut.h>
#include <math.h>

AssistentSpaceShip::AssistentSpaceShip() {
	// TODO Auto-generated constructor stub
}

AssistentSpaceShip::AssistentSpaceShip(float x, float y, float iAngle) {
	spaceShipPivotX = x;
	spaceShipPivotY = y;
	radius = GameSettings::ASSISENT_RADIUS;
	angle = iAngle;
	alive = true;
	newPivotX = calculateRelativeX();
	newPivotY = calculateRelativeY();
}



AssistentSpaceShip::~AssistentSpaceShip() {
	// TODO Auto-generated destructor stub
}

void AssistentSpaceShip::display(){

	//printf("JOEPIE, ik mag er ook zijn =D \n");
	newPivotX = calculateRelativeX();
	newPivotY = calculateRelativeY();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[4]);

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
		// calculate new pivot

		//printf("pivot: (%f,%f) with angle %f and pivot (%f,%f)\n", (pivotX+newPivotX), (pivotY+newPivotY), angle, pivotX, pivotY);

		glBegin(GL_QUADS);

			glTexCoord2f(0.0f,1.0f);
			glVertex3f((spaceShipPivotX+newPivotX-(GameSettings::ASSISTENT_SIZE[0]/2.0f)),	(spaceShipPivotY+newPivotY+(GameSettings::ASSISTENT_SIZE[1]/2.0f)),		1.02);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f((spaceShipPivotX+newPivotX-(GameSettings::ASSISTENT_SIZE[0]/2.0f)),	(spaceShipPivotY+newPivotY-(GameSettings::ASSISTENT_SIZE[1]/2.0f)),		1.02);
			glTexCoord2f(1.0f,0.0f);
			glVertex3f((spaceShipPivotX+newPivotX+(GameSettings::ASSISTENT_SIZE[0]/2.0f)),	(spaceShipPivotY+newPivotY-(GameSettings::ASSISTENT_SIZE[1]/2.0f)),		1.02);
			glTexCoord2f(1.0f,1.0f);
			glVertex3f((spaceShipPivotX+newPivotX+(GameSettings::ASSISTENT_SIZE[0]/2.0f)),	(spaceShipPivotY+newPivotY+(GameSettings::ASSISTENT_SIZE[1]/2.0f)),		1.02);

		glEnd();
		//reset to previous state
		glPopAttrib();

	glDisable(GL_TEXTURE_2D);

	angle += 5; // increase angle with one degree

}

float AssistentSpaceShip::calculateRelativeX()
{
	return cos(angle * GameSettings::PI / 180.0)*radius;
}

float AssistentSpaceShip::calculateRelativeY()
{
	return sin(angle * GameSettings::PI / 180.0)*radius;
}

void AssistentSpaceShip::updatePivot(float x, float y){
	spaceShipPivotX = x;
	spaceShipPivotY = y;
}

void AssistentSpaceShip::killAssistent()
{
	alive = false;
}

bool AssistentSpaceShip::isAlive()
{
	return alive;
}

float AssistentSpaceShip::getPositionX()
{
	return spaceShipPivotX+newPivotX-(GameSettings::ASSISTENT_SIZE[0]/2.0f);
}

float AssistentSpaceShip::getPositionY()
{
	return spaceShipPivotY+newPivotY-(GameSettings::ASSISTENT_SIZE[1]/2.0f);
}
