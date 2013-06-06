/*
 * Background.h
 *
 *  Created on: Jun 6, 2013
 *      Author: gerard
 */

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "GameSettings.h"

class Background {
private:
	int x,y,z;
	int width,height;
public:
	Background(int x,int y, int z, int width, int height);
	void draw();
	void animate();
	virtual ~Background();
};

#endif /* BACKGROUND_H_ */
