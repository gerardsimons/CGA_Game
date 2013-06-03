/*
 * GameSettings.h
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#ifndef GAMESETTINGS_H_
#define GAMESETTINGS_H_

class GameSettings {
public:
	static float GAME_SPEED;
	static float AIRPLANE_SIZE[];
	static float BULLET_SIZE[];
	static float OPPONENT_SPEED;
	static float BULLET_SPEED;
	GameSettings();
	virtual ~GameSettings();
};
#endif /* GAMESETTINGS_H_ */
