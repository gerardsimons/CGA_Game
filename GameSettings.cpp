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

float GameSettings::GAME_SPEED = .02;
float GameSettings::AIRPLANE_SIZE[] = {.5, .3};
float GameSettings::BULLET_SIZE[] = {.1, .05};
float GameSettings::OPPONENT_SPEED = .005;
float GameSettings::BULLET_SPEED = 0.02;

float GameSettings::NEXT_FLOW_TIME = 1500000;

std::vector<GLuint> GameSettings::Texture;
