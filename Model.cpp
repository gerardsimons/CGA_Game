/*
 * Model.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: gerard
 */

#include "Model.h"

Model::Model(const char* fileName)
{
	loadMesh(fileName);
}

Model::~Model() {
	// TODO Auto-generated destructor stub
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
	Vec3Df halfwayVector = Vec3Df(LightPos[0][0] + CamPos[0],LightPos[0][1] + CamPos[1],LightPos[0][2] + CamPos[2]);
	halfwayVector /= (LightPos[0].getLength() + CamPos.getLength());

	float nDotH = Vec3Df::dotProduct(halfwayVector,normal);

	float specularCoefficient = 3.0f;
	float specular = pow(nDotH,specularCoefficient);
	return color *= specular;
}

Vec3Df Model::lambertianLighting(Vec3Df &vertexPos,Vec3Df &normal, Vec3Df &color)
{
	float lambert = Vec3Df::dotProduct(vertexPos,normal);
	float distance = (vertexPos - GameSettings::LightPos[0]).getLength();
	//return Vec3Df(lambert * LightColor[0],lambert * LightColor[1],lambert * LightColor[2]);
	return Vec3Df(lambert / distance,lambert / distance,lambert / distance) * color;
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

void Model::move(float x, float y, float z)
{
	for (unsigned int i=0; i<mesh.vertices.size();++i)
	{

	}
}

Vec3Df Model::computeLighting(Vec3Df & vertexPos, Vec3Df & normal, unsigned int light, unsigned int index)
{

	Vec3Df color = Vec3Df(1,1,1);
	return lambertianLighting(vertexPos,normal,color) + blinnPhongShading(color,normal);;
	//return color;

}

void Model::drawModel()
{
	computeLighting();
	mesh.drawWithColors(lighting);
}
