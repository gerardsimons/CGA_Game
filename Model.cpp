/*
 * Model.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: gerard
 */

#include "Model.h"

Model::Model(const char* fileName,float x,float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	loadMesh(fileName);
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

Vec3Df Model::blinnPhongShading(Vec3Df &color, Vec3Df &normal)
{
	std::vector<Vec3Df> LightPos = GameSettings::LightPos;
	Vec3Df CamPos = GameSettings::CamPos;
	Vec3Df totalLight = Vec3Df(0,0,0);
	for(int i = 0 ; i < GameSettings::LightPos.size() ; i++)
	{
		Vec3Df lightColor = GameSettings::LightColor[i];
		Vec3Df halfwayVector = Vec3Df(LightPos[i][0] + CamPos[0],LightPos[i][1] + CamPos[1],LightPos[i][2] + CamPos[2]);
		halfwayVector /= (LightPos[0].getLength() + CamPos.getLength());

		float nDotH = Vec3Df::dotProduct(halfwayVector,normal);

		float specularCoefficient = 2.0f;
		float specular = pow(nDotH,specularCoefficient);
		totalLight += (color * specular * lightColor);
	}
	return totalLight;
}

Vec3Df Model::ambientLighting(Vec3Df &color)
{
	float ambientFactor = 0.1f / GameSettings::LightPos.size();
	return Vec3Df(ambientFactor * color[0],ambientFactor * color[1],ambientFactor * color[2]);
}

Vec3Df Model::lambertianLighting(Vec3Df &vertexPos,Vec3Df &normal, Vec3Df &color)
{
	Vec3Df totalLight = Vec3Df(0,0,0);
	for(int i = 0 ; i < GameSettings::LightPos.size() ; i++)
	{
		Vec3Df lightColor = GameSettings::LightColor[i];
		Vec3Df LightPos = GameSettings::LightPos[i];
		Vec3Df distanceVector = LightPos - vertexPos;
		float lambert = Vec3Df::dotProduct(distanceVector,normal);
		float distance = distanceVector.getLength();
		distance = 3.0f;
		totalLight += Vec3Df(lambert / distance,lambert / distance,lambert / distance) * color * lightColor;
	}
	return totalLight;
}

void Model::computeLighting()
{
	//std::vector<Vec3Df> *result=&lighting;
	std::vector<Vec3Df> *result = &lighting;

	for (unsigned int i=0; i<mesh.vertices.size();++i)
	{
		(*result)[i]=Vec3Df();
		for (int l=0; l<GameSettings::LightPos.size();++l)
			(*result)[i]+=computeLighting(mesh.vertices[i].p, mesh.vertices[i].n, l, i);
	}
}

void Model::move(float deltaX, float deltaY, float deltaZ)
{
	x += deltaX;
	y += deltaY;
	z += deltaZ;
}

void Model::rotate(float rotXDelta, float rotYDelta, float rotZDelta)
{
	rotX += rotXDelta;
	rotY += rotYDelta;
	rotZ += rotZDelta;
}

Vec3Df Model::computeLighting(Vec3Df & vertexPos, Vec3Df & normal, unsigned int light, unsigned int index)
{

	Vec3Df color = Vec3Df(1,1,1);
	return ambientLighting(color) + lambertianLighting(vertexPos,normal,color) + blinnPhongShading(color,normal);;
	//return lambertianLighting(vertexPos,normal,color);
	//return blinnPhongShading(color,normal);
	//return ambientLighting(color);
	//return color;

}

void Model::drawModel()
{
	computeLighting();

	glPushMatrix();
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glRotatef(rotZ,0,0,1);
	//glTranslatef(x,y,z);

	mesh.drawWithColors(lighting);

	glPopMatrix();
}
