/*
 * LightManager.h
 *
 *  Created on: Jun 5, 2013
 *      Author: gerard
 *
 *      This static class takes care of managing the lights and computing colors for other objects
 */

#ifndef LIGHTMANAGER_H_
#define LIGHTMANAGER_H_

#include <vector>
#include "Vec3D.h"
#include "GameSettings.h"

class LightManager {
public:
	static std::vector<Vec3Df> LightPos;
	static std::vector<Vec3Df> DiffuseColor;
	static std::vector<Vec3Df> SpecularColor;
	static std::vector<float> SpecularPower;
	static std::vector<float> DiffusePower;
	static Vec3Df AmbientLight;
	static float SpecularHardness;

	static void moveLight(int,float,float,float);

	static Vec3Df blinnPhongShading(Vec3Df &color, Vec3Df &normal, Vec3Df &vertex);
	static Vec3Df lambertianLighting(Vec3Df &vertexPos,Vec3Df &normal, Vec3Df &color);
	static void addLight(Vec3Df pos,Vec3Df diffuseColor, Vec3Df specularColor, float specularPower, float diffusePower);
	static Vec3Df shading(Vec3Df &normal,Vec3Df &color,Vec3Df &vertex,float multiplier);
	static void animateLights();
};

#endif /* LIGHTMANAGER_H_ */
