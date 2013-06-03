#include "SpaceShip.h"
/*

 * OpponentSpaceShip.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#ifndef OPPONENTSPACESHIP_H_
#define OPPONENTSPACESHIP_H_

class OpponentSpaceShip : public SpaceShip {
public:
	OpponentSpaceShip();
	OpponentSpaceShip(float x, float y);
	virtual ~OpponentSpaceShip();
	void display();
};

#endif /* OPPONENTSPACESHIP_H_ */
