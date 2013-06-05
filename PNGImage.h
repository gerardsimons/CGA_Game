/*
 * PNGImage.h
 *
 *  Created on: Jun 5, 2013
 *      Author: gerard
 */

#ifndef PNGIMAGE_H_
#define PNGIMAGE_H_

#include <iostream>
#include <fstream>
#include <math.h>
#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/gl.h>

class PNGImage {
public:
	int sizeX, sizeY;
	GLubyte *data;
	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);
	PNGImage(const char *filename,bool hasAlpha);
	~PNGImage(){
		if(data)
			delete [] data;
	}
};

#endif /* PNGIMAGE_H_ */
