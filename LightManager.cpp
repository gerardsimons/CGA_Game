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
float LightManager::AmbientLight = 0.2f;
float LightManager::SpecularHardness = 2.3f;

Vec3Df LightManager::shading(Vec3Df &normal, Vec3Df &color, Vec3Df &vertex, float multiplier)
{
	Vec3Df CamPos = GameSettings::CamPos;
	Vec3Df totalLight = Vec3Df(0,0,0);
	for(int i = 0 ; i < LightPos.size() ; i++)
	{
		Vec3Df viewDir = CamPos - vertex;
		viewDir /= viewDir.getLength();
		Vec3Df lightDir = LightPos[i] - vertex;
		float distance = lightDir.getLength();
		lightDir /= distance;

		//Diffuse component
		Vec3Df diffuse = Vec3Df::dotProduct(lightDir,normal) * DiffusePower[i] * DiffuseColor[i] * color;

		Vec3Df H = (lightDir + viewDir);
		H /= H.getLength();

		//Vec3Df halfwayVector = Vec3Df(LightPos[i][0] + CamPos[0],LightPos[i][1] + CamPos[1],LightPos[i][2] + CamPos[2]);
		//halfwayVector /= (LightPos[0].getLength() + CamPos.getLength());


		float nDotH = Vec3Df::dotProduct(H,normal);
		float intensity = pow(nDotH,SpecularHardness);

		Vec3Df specular = intensity * SpecularPower[i] * SpecularColor[i] * color;

		totalLight += specular + diffuse;

	}
	return totalLight + (totalLight * Vec3Df(AmbientLight,AmbientLight,AmbientLight) * multiplier);
	//return color;
}

void LightManager::animateLights()
{
	float xUpperBound = 4.0f;
	float xLowerBound = -4.0f;
	for(int i = 0 ; i < LightPos.size() ; i++)
	{
		//LightPos[i][0] -= 0.05f;
	}
}

void LightManager::addLight(Vec3Df pos,Vec3Df diffuseColor, Vec3Df specularColor, float specularPower, float diffusePower)
{
	LightPos.push_back(pos);
	DiffuseColor.push_back(diffuseColor);
	SpecularColor.push_back(specularColor);
	SpecularPower.push_back(specularPower);
	DiffusePower.push_back(diffusePower);
}
