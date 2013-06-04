
/*
 * GameSettings.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#ifndef GAMESETTINGS_H_
#define GAMESETTINGS_H_

#include <GL/glut.h>
#include <stdlib.h>
#include "stdio.h"
#include <vector>

class GameSettings {
public:
	static float GAME_SPEED;
	static float AIRPLANE_SIZE[];
	static float BULLET_SIZE[];
	static float OPPONENT_SPEED;
	static float BULLET_SPEED;

	static float NEXT_FLOW_TIME;

	static std::vector<GLuint> Texture;

	GameSettings();
	virtual ~GameSettings();
};
#endif /* GAMESETTINGS_H_ */
