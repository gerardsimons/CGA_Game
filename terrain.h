#ifndef TERRAIN_H
#define TERRAIN_H

#ifdef WIN32
#include <Windows.h>
#endif

#include <stdlib.h>
#include <GL/glut.h>
#include "GameSettings.h"
#include "stdio.h"
#include "Vec3D.h"
#include <vector>
#include "loadppm.h"
#include "LightManager.h"


/* Terrain.h
 *
 *  Created on: Jun 3, 2013
 *      Author: gerardsimons
 */


class Terrain {
private:
	std::vector<float> SurfaceVertices3f;
	std::vector<float> SurfaceNormals3f;
	std::vector<float> SurfaceColors3f;
	std::vector<float> SurfaceTexCoords2f;
	std::vector<GLuint> Texture;

public:
	Vec3Df defaultColor;
	void initTexture();
	Terrain(int,int,float,float,float,float,float,float,float);
	void initSurfaceMesh(int,int);
	virtual ~Terrain();
	void display();
	void drawQuad();
};

#endif /* TERRAIN_H */
