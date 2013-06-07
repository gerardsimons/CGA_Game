/*
 * Model.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: gerard
 */

#include "Model.h"
#include "Bullet.h"

Model::Model(const char* fileName,float x,float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	loadMesh(fileName);

	bullitsShot = new std::vector<Bullet>();
	health = GameSettings::INIT_HEALTH_FINAL_BOSS;
}

Model::~Model() {

}


void Model::loadMesh(const char * fileName){

	//this function loads a mesh
    mesh.loadMesh(fileName);

	lighting.resize(mesh.vertices.size());

	MeshMaterial.resize(mesh.vertices.size());
	for (int i=0; i<mesh.vertices.size();++i)
		MeshMaterial[i]=Vec3Df(0,0,0);

	computeLighting();
}

void Model::computeLighting()
{
	//std::vector<Vec3Df> *result=&lighting;
	std::vector<Vec3Df> *result = &lighting;

	for (unsigned int i=0; i<mesh.vertices.size();++i)
	{
		(*result)[i]=Vec3Df();
		for (int l=0; l < LightManager::LightPos.size();++l)
			(*result)[i]+=computeLighting(mesh.vertices[i].p, mesh.vertices[i].n, l, i);
	}
}

void Model::move(float deltaX, float deltaY, float deltaZ)
{
	x += deltaX;
	y += deltaY;
	z += deltaZ;
}

void Model::moveToX(float deltaX)
{
	y = deltaX;
}

void Model::moveToY(float deltaY)
{
	y = deltaY;
}

void Model::rotate(float rotXDelta, float rotYDelta, float rotZDelta)
{
	rotX += rotXDelta;
	rotY += rotYDelta;
	rotZ += rotZDelta;
}

Vec3Df Model::computeLighting(Vec3Df & vertexPos, Vec3Df & normal, unsigned int light, unsigned int index)
{

	Vec3Df color = Vec3Df(0.5f,0.5f,0.5f);
	return LightManager::shading(normal,color,vertexPos,0.3f);
	//return color;
}

void Model::drawModel()
{
	computeLighting();

	glPushMatrix();
	glTranslatef(-x,-y,-z);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glRotatef(rotZ,0,0,1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(x,y,z);

	mesh.drawWithColors(lighting);

	glPopMatrix();

}

float Model::getPositionX()
{
	return this->x;
}
float Model::getPositionY()
{
	return this->y;
}

void Model::shoot(){

	Bullet b1 = Bullet(this->x, (this->y), 	-1);
	Bullet b2 = Bullet(this->x, (this->y-.3)	, 	-1);
	Bullet b3 = Bullet(this->x, (this->y-.6), 	-1);
	bullitsShot->push_back( b1 );
	bullitsShot->push_back( b2 );
	bullitsShot->push_back( b3 );
	printf("I have shot %d times \n", bullitsShot->size());

}

void Model::drawBossBullets()
{

	// render bullets
	for(unsigned int i = 0; i<bullitsShot->size(); i++)
	{
		bullitsShot->at(i).display();
	}
}

std::vector<Bullet> * Model::getBulletList()
{
	return bullitsShot;
}

void Model::removeBullet( int index )
{
	//printf( "removebullet: %f", bullitsShot.at(index).getPositionX() );
	bullitsShot->erase( bullitsShot->begin() + index );
}

void Model::decreaseHealth()
{
	health--;
}

float Model::getHealth()
{
	return health;
}
