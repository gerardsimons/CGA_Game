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


	int v1 = rand() % 3;
	v1 = 1;
	int i = 0;
	SurfaceVertices3f.resize(zSize * xSize * 12 * (1.0f / surfaceSize));
	SurfaceNormals3f.resize(zSize * xSize * 12 * (1.0f / surfaceSize));
	SurfaceColors3f.resize(zSize * xSize * 12);
	for(float x = 0 ; x < xSize ; x += surfaceSize)
	{
		int v2 = rand() % 10;
		for(float z = 0 ; z < zSize ; z += surfaceSize)
		{

			SurfaceVertices3f[i]=x;
			SurfaceVertices3f[i+1]=z;
			SurfaceVertices3f[i+2]=cos(x) + sin(z);

			SurfaceVertices3f[i+3]=x+surfaceSize;
			SurfaceVertices3f[i+4]=z;
			SurfaceVertices3f[i+5]=cos(x+surfaceSize) + sin(z);

			SurfaceVertices3f[i+6]=x+surfaceSize;
			SurfaceVertices3f[i+7]=z+surfaceSize;
			SurfaceVertices3f[i+8]=cos(x+surfaceSize) + sin(z+surfaceSize);

			SurfaceVertices3f[i+9]=x;
			SurfaceVertices3f[i+10]=z+surfaceSize;
			SurfaceVertices3f[i+11]=cos(x) + sin(z+surfaceSize);

			//define normals
			SurfaceNormals3f[i]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+1]=0;	//y
			SurfaceNormals3f[i+2]=sin(x) / surfaceSize;		//z

			SurfaceNormals3f[i+3]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+4]=0;
			SurfaceNormals3f[i+5]=sin(x) / surfaceSize;		//z

			SurfaceNormals3f[i+6]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+7]=0;
			SurfaceNormals3f[i+8]=sin(x) / surfaceSize;		//z

			SurfaceNormals3f[i+9]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+10]=0;
			SurfaceNormals3f[i+11]=sin(x) / surfaceSize;	//z

			/* Colors
			SurfaceColors3f[i+0]=0.05;
			SurfaceColors3f[i+1]=1;
			SurfaceColors3f[i+2]=cos(x);

			SurfaceColors3f[i+3]=cos(x+surfaceSize);
			SurfaceColors3f[i+4]=1;
			SurfaceColors3f[i+5]=cos(x+surfaceSize);

			SurfaceColors3f[i+6]=cos(x+surfaceSize);
			SurfaceColors3f[i+7]=1;
			SurfaceColors3f[i+8]=cos(x+surfaceSize);

			SurfaceColors3f[i+9]=cos(x);
			SurfaceColors3f[i+10]=1;
			SurfaceColors3f[i+11]=cos(x);
			*/
			/*
			SurfaceVertices3f[i]=x;
			SurfaceVertices3f[i+1]=cos(x);// + sin(z * v1);
			SurfaceVertices3f[i+2]=z;

			SurfaceVertices3f[i+3]=x+surfaceSize;
			SurfaceVertices3f[i+4]=cos((x+surfaceSize));// + sin(z * v1);
			SurfaceVertices3f[i+5]=z;

			SurfaceVertices3f[i+6]=x+surfaceSize;
			SurfaceVertices3f[i+7]=cos((x+surfaceSize) * v1);// + sin((z+surfaceSize)*v1);
			SurfaceVertices3f[i+8]=z+surfaceSize;

			SurfaceVertices3f[i+9]=x;
			SurfaceVertices3f[i+10]=cos(x * v1);// + sin((z + surfaceSize) * v1);
			SurfaceVertices3f[i+11]=z + surfaceSize;


			SurfaceNormals3f[i]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+1]=sin(x) / surfaceSize;	;	//y
			SurfaceNormals3f[i+2]=0;	//z

			SurfaceNormals3f[i+3]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+4]=sin(x) / surfaceSize;
			SurfaceNormals3f[i+5]=0;		//z

			SurfaceNormals3f[i+6]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+7]=sin(x) / surfaceSize;
			SurfaceNormals3f[i+8]=0;		//z

			SurfaceNormals3f[i+9]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+10]=sin(x) / surfaceSize;
			SurfaceNormals3f[i+11]=0;	//z


			SurfaceNormals3f[i]=0;    	//x
			SurfaceNormals3f[i+1]=sin(x) / surfaceSize;	;	//y
			SurfaceNormals3f[i+2]=cos(x) / surfaceSize;	//z

			SurfaceNormals3f[i+3]=0;    	//x
			SurfaceNormals3f[i+4]=sin(x) / surfaceSize;
			SurfaceNormals3f[i+5]=cos(x) / surfaceSize;		//z

			SurfaceNormals3f[i+6]=0;    	//x
			SurfaceNormals3f[i+7]=sin(x) / surfaceSize;
			SurfaceNormals3f[i+8]=cos(x) / surfaceSize;		//z

			SurfaceNormals3f[i+9]=0;    	//x
			SurfaceNormals3f[i+10]=sin(x) / surfaceSize;
			SurfaceNormals3f[i+11]=cos(x) / surfaceSize;	//z

			/*
			SurfaceVertices3f[i]=x;
			SurfaceVertices3f[i+1]=y;
			SurfaceVertices3f[i+2]=cos(x);

			SurfaceVertices3f[i+3]=x+surfaceSize;
			SurfaceVertices3f[i+4]=y;
			SurfaceVertices3f[i+5]=cos(x+surfaceSize);

			SurfaceVertices3f[i+6]=x+surfaceSize;
			SurfaceVertices3f[i+7]=y+surfaceSize;
			SurfaceVertices3f[i+8]=cos(x+surfaceSize);

			SurfaceVertices3f[i+9]=x;
			SurfaceVertices3f[i+10]=y+surfaceSize;
			SurfaceVertices3f[i+11]=cos(x);

			//define normals
			SurfaceNormals3f[i]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+1]=0;	//y
			SurfaceNormals3f[i+2]=sin(x) / surfaceSize;		//z

			SurfaceNormals3f[i+3]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+4]=0;
			SurfaceNormals3f[i+5]=sin(x) / surfaceSize;		//z

			SurfaceNormals3f[i+6]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+7]=0;
			SurfaceNormals3f[i+8]=sin(x) / surfaceSize;		//z

			SurfaceNormals3f[i+9]=cos(x) / surfaceSize;    	//x
			SurfaceNormals3f[i+10]=0;
			SurfaceNormals3f[i+11]=sin(x) / surfaceSize;	//z
			*/


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
		//glColor3fv(&(SurfaceColors3f[3*vIndex]));
		glColor3f(0.9,0.85,0.35);
		float *vertex = &(SurfaceVertices3f[vIndex]);
		float *normal = &(SurfaceNormals3f[vIndex]);
		//printf("Drawing vertex #%d = (%f,%f,%f)\n",i,&vertex,&(vertex+1),&(vertex+2));

		glNormal3f(*normal,*(normal+1),*(normal+2));
		glVertex3f(*vertex,*(vertex+1),*(vertex+2));
	}
	glEnd();
}
