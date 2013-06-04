/*
 * AssistentSpaceShip.h
 *
 *  Created on: Jun 4, 2013
 *      Author: nathanmol
 */

#ifndef ASSISTENTSPACESHIP_H_
#define ASSISTENTSPACESHIP_H_

class AssistentSpaceShip {
private:
	float spaceShipPivotX; float spaceShipPivotY;
	float radius; float angle;
	bool alive;
	float newPivotX; float newPivotY;
public:
	AssistentSpaceShip();
	AssistentSpaceShip(float x, float y, float iAngle);
	virtual ~AssistentSpaceShip();

	void display();
	void updatePivot(float x, float y);

	float calculateRelativeX();
	float calculateRelativeY();

	void killAssistent();
	bool isAlive();

	float getPositionX();
	float getPositionY();
};

#endif /* ASSISTENTSPACESHIP_H_ */


