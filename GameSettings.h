
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
#include "Vec3D.h"

class GameSettings {
public:
	static float INIT_HEALTH;
	static float INIT_HEALTH_FINAL_BOSS;

	static float GAME_SPEED;
	static float AIRPLANE_SIZE[];
	static float ASSISTENT_SIZE[];
	static float FINAL_BOSS_SIZE[];
	static float BULLET_SIZE[];
	static float OPPONENT_SPEED;
	static float BULLET_SPEED;
	static float ASSISENT_RADIUS;

	static float OPPONENT_SHOOT_TIME;
	static float FINAL_BOSS_SHOOT_TIME;

	static int NUMBER_OF_FLOWS;

	static float MAX_RANGE;

	static float NEXT_FLOW_TIME;

	static float BULLET_LOCK;

	static Vec3Df CamRot;
	static Vec3Df CamPos;

	static std::vector<GLuint> Texture;

	static float PI;

	static void updateCamera(float xDelta, float yDelta, float zDelta);
	static void updateCameraRot(float xDelta, float yDelta, float zDelta);

	GameSettings();
	virtual ~GameSettings();
};
#endif /* GAMESETTINGS_H_ */
