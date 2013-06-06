/*
 * LightManager.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: gerard
 */

#include "LightManager.h"

std::vector<Vec3Df> LightManager::LightPos;
std::vector<Vec3Df> LightManager::DiffuseColor;
std::vector<Vec3Df> LightManager::SpecularColor;
std::vector<float> LightManager::SpecularPower;
std::vector<float> LightManager::DiffusePower;
Vec3Df LightManager::AmbientLight = Vec3Df(0.05f,0.05f,0.05f);
float LightManager::SpecularHardness = 4.3f;

Vec3Df LightManager::shading(Vec3Df &normal, Vec3Df &color, Vec3Df &vertex, float multiplier)
{
	normal.normalize();
	//return Vec3Df(.5,.1,.1);
	//return lambertianLighting(vertex,normal,color);
	return blinnPhongShading(color,normal,vertex) + AmbientLight;
	//return lambertianLighting(vertex,normal,color) + blinnPhongShading(color,normal,vertex);//+
}

Vec3Df LightManager::blinnPhongShading(Vec3Df &color, Vec3Df &normal, Vec3Df &vertex)
{
	Vec3Df total = Vec3Df(0,0,0);
	for(int i = 0 ; i < LightPos.size() ; i++)
	{
		Vec3Df CamPos = GameSettings::CamPos;
		Vec3Df viewDir = CamPos - vertex;
		Vec3Df lightDir = LightPos[i] - vertex;
		float distance = lightDir.getLength();
		distance = 1;
		lightDir.normalize();

		Vec3Df H = Vec3Df(lightDir + viewDir);
		H.normalize();

		float NdotH = Vec3Df::dotProduct(normal,H);
		float intensity = pow(NdotH, SpecularHardness);
		total += SpecularColor[i] * SpecularPower[i] * intensity / distance;
	}
	total += AmbientLight;
	return total;
}


Vec3Df LightManager::lambertianLighting(Vec3Df &vertexPos,Vec3Df &normal, Vec3Df &color)
{
	Vec3Df totalLight = Vec3Df(0,0,0);
	for(int i = 0 ; i < LightPos.size() ; i++)
	{
		Vec3Df light = LightPos[i];
		float lambert = Vec3Df::dotProduct(vertexPos,normal);
		float distance = (light - vertexPos).getLength();
		//distance = 1.0f;
		totalLight += Vec3Df(lambert * DiffuseColor[i][0],lambert * DiffuseColor[i][1],lambert * DiffuseColor[i][2]);
	}
	return totalLight;
}

void LightManager::moveLight(int index, float xDelta, float yDelta, float zDelta)
{
	LightPos[index][0] += xDelta;
	LightPos[index][1] += yDelta;
	LightPos[index][2] += zDelta;
}

void LightManager::addLight(Vec3Df pos,Vec3Df diffuseColor, Vec3Df specularColor, float specularPower, float diffusePower)
{
	LightPos.push_back(pos);
	DiffuseColor.push_back(diffuseColor);
	SpecularColor.push_back(specularColor);
	SpecularPower.push_back(specularPower);
	DiffusePower.push_back(diffusePower);
}
