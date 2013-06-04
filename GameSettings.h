
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
	static float GAME_SPEED;
	static float AIRPLANE_SIZE[];
	static float ASSISTENT_SIZE[];
	static float BULLET_SIZE[];
	static float OPPONENT_SPEED;
	static float BULLET_SPEED;
	static float ASSISENT_RADIUS;

	static float MAX_RANGE;

	static float NEXT_FLOW_TIME;

	static std::vector<Vec3Df> LightPos;
	static std::vector<Vec3Df> LightColor;
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
