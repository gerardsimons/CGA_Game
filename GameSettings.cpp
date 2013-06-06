/*
 * GameSettings.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: nathanmol
 */

#include "GameSettings.h"

GameSettings::GameSettings() {
	// TODO Auto-generated constructor stub

}

GameSettings::~GameSettings() {
	// TODO Auto-generated destructor stub
}

float GameSettings::INIT_HEALTH = 5;
float GameSettings::INIT_HEALTH_FINAL_BOSS = 50;

float GameSettings::GAME_SPEED = .02;
float GameSettings::AIRPLANE_SIZE[] = {.6, .3};
float GameSettings::ASSISTENT_SIZE[] = {.2, .1};
float GameSettings::FINAL_BOSS_SIZE[] = {1, .7};
float GameSettings::BULLET_SIZE[] = {.1, .05};
float GameSettings::OPPONENT_SPEED = .005;
float GameSettings::BULLET_SPEED = 0.02;
float GameSettings::ASSISENT_RADIUS = .4;

int GameSettings::NUMBER_OF_FLOWS = 3;

float GameSettings::MAX_RANGE = 4;

//float GameSettings::NEXT_FLOW_TIME = 1500000;

float GameSettings::NEXT_FLOW_TIME = 5000000;


//float GameSettings::PI = 3.14159265;
float GameSettings::PI = 22/7;

Vec3Df GameSettings::CamPos = Vec3Df(1.2,0.4,5);
//Vec3Df GameSettings::CamPos = Vec3Df(1,2,5);
Vec3Df GameSettings::CamRot = Vec3Df(0,0,0);

void GameSettings::updateCamera(float xDelta, float yDelta, float zDelta)
{
	CamPos[0] += xDelta;
	CamPos[1] += yDelta;
	CamPos[2] += zDelta;
}

void GameSettings::updateCameraRot(float xDelta, float yDelta, float zDelta)
{
	CamRot[0] += xDelta;
	CamRot[1] += yDelta;
	CamRot[2] += zDelta;
}



std::vector<GLuint> GameSettings::Texture;
