#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "Vector3.h"

using namespace std;

class Sphere : public Object
{
private:
	Vector3 center;
	float radius;

public:
	Sphere();
	Sphere(Vector3 center, float radius, float refractiveCoefficient, float reflectionCoefficient, Vector3 color);

	Vector3 getCenter();
	float getRadius();
	bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection);
	Vector3 getNormalIn(Vector3 pointOfIntersection);

};

#endif // SPHERE_H