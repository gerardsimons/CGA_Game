/*
 * Model.h
 *
 *  Created on: Jun 4, 2013
 *      Author: gerard
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "Vec3D.h"
#include <vector>
#include "GameSettings.h"

class Model {
public:
	Model(const char*);
	void loadMesh(const char*);
	void computeLighting();
	Vec3Df computeLighting(Vec3Df & vertexPos, Vec3Df & normal, unsigned int light, unsigned int index);
	Vec3Df blinnPhongShading(Vec3Df &color, Vec3Df &normal);
	Vec3Df lambertianLighting(Vec3Df &vertexPos,Vec3Df &normal, Vec3Df &color);
	void drawModel();
	void move(float,float,float);
	virtual ~Model();
private:
	Mesh mesh;
	std::vector<Vec3Df> lighting;
	std::vector<Vec3Df> MeshMaterial;
};

#endif /* MODEL_H_ */
