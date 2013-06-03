#include "terrain.h"
#include <GL/glut.h>

/*
 * SpaceShip.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: Gerard Simons
 */

Terrain::Terrain(int xSize, int zSize, float surfaceSize) {
	// TODO Auto-generated constructor stub

	
	int i = 0;
	SurfaceVertices3f.resize(zSize * xSize * 12);
	for(float x = 0 ; x < xSize ; x += surfaceSize)
	{
		for(float z = 0 ; z < zSize ; z += surfaceSize)
		{
			
			SurfaceVertices3f[i]=x;
			SurfaceVertices3f[i+1]=cos(x);
			SurfaceVertices3f[i+2]=z;

			SurfaceVertices3f[i+3]=x+surfaceSize;
			SurfaceVertices3f[i+4]=cos(x+surfaceSize);
			SurfaceVertices3f[i+5]=z;

			SurfaceVertices3f[i+6]=x+surfaceSize;
			SurfaceVertices3f[i+7]=cos(x+surfaceSize);
			SurfaceVertices3f[i+8]=z+surfaceSize;

			SurfaceVertices3f[i+9]=x;
			SurfaceVertices3f[i+10]=cos(x);
			SurfaceVertices3f[i+11]=z+surfaceSize;
			i += 12;

		}
	}
}

Terrain::~Terrain() {
	// TODO Auto-generated destructor stub
}

void Terrain::display()
{
	glBegin(GL_QUADS);
	//printf("SurfaceVertices3f.size() = %d\n",SurfaceVertices3f.size());
	for (int vIndex = 0 ; vIndex < SurfaceVertices3f.size() ; vIndex += 3)
	{
		//glTexCoord2fv(&(SurfaceTexCoords2f[2*vIndex]));
		//glNormal3fv(&(SurfaceNormals3f[3*vIndex]));
		//glColor3fv(&(SurfaceColors3f[3*vIndex]));

		float *vertex = &(SurfaceVertices3f[vIndex]);

		//printf("Drawing vertex #%d = (%f,%f,%f)\n",i,&vertex,&(vertex+1),&(vertex+2));

		glVertex3f(*vertex,*(vertex+1),*(vertex+2));
	}
	glEnd();
}
