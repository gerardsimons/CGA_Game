#include "terrain.h"
#include <GL/glut.h>
#include "GameSettings.h"

#define PI 3.14159265

/*
 * SpaceShip.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: Gerard Simons
 */

Terrain::Terrain(int xSize, int zSize, float surfaceSize, float startX, float startZ) {



	int newSize = static_cast<int>(xSize / surfaceSize * zSize / surfaceSize * 12);
		printf("new size vertices array=%d\n",newSize);

	int i = 0;

	SurfaceVertices3f.resize(newSize);
	SurfaceNormals3f.resize(newSize);
	SurfaceColors3f.resize(newSize);
	SurfaceTexCoords2f.resize(static_cast<int>(xSize / surfaceSize * zSize / surfaceSize * 12));
	float zModifier = 0.3f;
	float xModifier = 0.8f;

	//Maximum value possible
	float yTop = zModifier * sin(.5 * PI) + xModifier * cos(0);
	int texIndex = 0;
	float xPeriod = 2 * PI / xModifier;
	printf("xPeriod=%f\n",xPeriod);
	for(float x = 0 ; x < xSize; x += surfaceSize)
	{
		for(float z = 0 ; z < zSize; z += surfaceSize)
		{
			SurfaceVertices3f[i]=x+startX;					//x
			SurfaceVertices3f[i+1]=xModifier*cos(x) + zModifier*sin(z)-yTop; //y
			SurfaceVertices3f[i+2]=z+startZ;				//z

			SurfaceVertices3f[i+3]=x+surfaceSize+startX;
			SurfaceVertices3f[i+4]=xModifier*cos(x+surfaceSize) + zModifier*sin(z)-yTop;
			SurfaceVertices3f[i+5]=z+startZ;

			SurfaceVertices3f[i+6]=x+surfaceSize+startX;
			SurfaceVertices3f[i+7]=xModifier*cos(x+surfaceSize) + zModifier*sin(z+surfaceSize)-yTop;
			SurfaceVertices3f[i+8]=z+surfaceSize+startZ;

			SurfaceVertices3f[i+9]=x+startX;
			SurfaceVertices3f[i+10]=xModifier*cos(x) + zModifier*sin(z+surfaceSize)-yTop;
			SurfaceVertices3f[i+11]=z+surfaceSize+startZ;

			SurfaceTexCoords2f[texIndex]=x;
			SurfaceTexCoords2f[texIndex+1]=z;

			SurfaceTexCoords2f[texIndex+2]=x+surfaceSize;
			SurfaceTexCoords2f[texIndex+3]=z;

			SurfaceTexCoords2f[texIndex+4]=x+surfaceSize;
			SurfaceTexCoords2f[texIndex+5]=z+surfaceSize;

			SurfaceTexCoords2f[texIndex+6]=x;
			SurfaceTexCoords2f[texIndex+7]=z+surfaceSize;

			SurfaceColors3f[i+0]=0.05;
			SurfaceColors3f[i+1]=xModifier*cos(x) + zModifier*sin(z)-yTop;;
			SurfaceColors3f[i+2]=cos(x);

			SurfaceColors3f[i+3]=cos(x+surfaceSize);
			SurfaceColors3f[i+4]=xModifier*cos(x) + zModifier*sin(z)-yTop;;
			SurfaceColors3f[i+5]=cos(x+surfaceSize);

			SurfaceColors3f[i+6]=cos(x+surfaceSize);
			SurfaceColors3f[i+7]=xModifier*cos(x) + zModifier*sin(z)-yTop;;
			SurfaceColors3f[i+8]=cos(x+surfaceSize);

			SurfaceColors3f[i+9]=cos(x);
			SurfaceColors3f[i+10]=xModifier*cos(x) + zModifier*sin(z)-yTop;;
			SurfaceColors3f[i+11]=cos(x);

			Vec3Df v1 = Vec3Df(SurfaceVertices3f[i] - SurfaceVertices3f[i+3],SurfaceVertices3f[i+1] - SurfaceVertices3f[i+4],SurfaceVertices3f[i+2] - SurfaceVertices3f[i+5]);
			Vec3Df v2 = Vec3Df(SurfaceVertices3f[i+6] - SurfaceVertices3f[i+3],SurfaceVertices3f[i+7] - SurfaceVertices3f[i+4],SurfaceVertices3f[i+8] - SurfaceVertices3f[i+5]);

			Vec3Df normal = Vec3Df::crossProduct(v1,v2);




			SurfaceNormals3f[i]=normal[0];    	//x
			SurfaceNormals3f[i+1]=normal[1];	//y
			SurfaceNormals3f[i+2]=normal[2];		//z

			SurfaceNormals3f[i+3]=normal[0];    	//x
			SurfaceNormals3f[i+4]=normal[1];	//y
			SurfaceNormals3f[i+5]=normal[2];		//z

			SurfaceNormals3f[i+6]=normal[0];    	//x
			SurfaceNormals3f[i+7]=normal[1];	//y
			SurfaceNormals3f[i+8]=normal[2];		//z

			SurfaceNormals3f[i+9]=normal[0];    	//x
			SurfaceNormals3f[i+10]=normal[1];	//y
			SurfaceNormals3f[i+11]=normal[2];		//z

			i += 12;
			texIndex += 8;
		}

	}


	//printf("i=%d\n",i);

}

Terrain::~Terrain() {
	// TODO Auto-generated destructor stub
}

void Terrain::display()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GameSettings::Texture[3]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,  GL_LINEAR);
	glBegin(GL_QUADS);
	//printf("SurfaceVertices3f.size() = %d\n",SurfaceVertices3f.size());
	int texIndex = 0;
	for (int vIndex = 0 ; vIndex < SurfaceVertices3f.size() ; vIndex += 3)
	{
		glColor3f(0.9,0.85,0.35);
		float *vertex = &(SurfaceVertices3f[vIndex]);
		float *normal = &(SurfaceNormals3f[vIndex]);
		float *tex = &(SurfaceTexCoords2f[texIndex]);
		float *color = &(SurfaceTexCoords2f[texIndex]);
		//printf("Drawing vertex #%d = (%f,%f,%f)\n",i,&vertex,&(vertex+1),&(vertex+2));
		glTexCoord2f(*tex,*(tex+1));
		glNormal3f(*normal,*(normal+1),*(normal+2));
		glVertex3f(*vertex,*(vertex+1),*(vertex+2));
		texIndex += 2;
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
}
