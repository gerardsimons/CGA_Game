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
class Bullet;

class Model {
public:
	Model(const char*,float,float,float);
	void loadMesh(const char*);
	void computeLighting();
	Vec3Df computeLighting(Vec3Df & vertexPos, Vec3Df & normal, unsigned int light, unsigned int index);
	Vec3Df blinnPhongShading(Vec3Df &color, Vec3Df &normal);
	Vec3Df lambertianLighting(Vec3Df &vertexPos,Vec3Df &normal, Vec3Df &color);
	Vec3Df ambientLighting(Vec3Df &color);
	void drawModel();
	float getPositionX();
	float getPositionY();
	void move(float,float,float);
	void rotate(float,float,float);
	virtual ~Model();

	void shoot();
	void drawBossBullets();
	std::vector<Bullet> * getBulletList();
	void removeBullet( int index );
	void decreaseHealth();
	float getHealth();
private:
	Mesh mesh;
	float x;
	float y;
	float z;
	float rotX;
	float rotY;
	float rotZ;
	std::vector<Vec3Df> lighting;
	std::vector<Vec3Df> MeshMaterial;

	std::vector<Bullet> * bullitsShot;
	float health;
};

#endif /* MODEL_H_ */
