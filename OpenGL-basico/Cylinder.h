#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Vector3.h"

using namespace std;

class Cylinder : public Object
{
private:
	Vector3 baseCenter1, baseCenter2;
	float radius;
	bool intersectBase(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection, Vector3 baseCenter);
	bool intersectBody(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection);

public:
	Cylinder(Vector3 baseCenter1, Vector3 baseCenter2, float radius, float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color);
	bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection);
	Vector3 getNormalIn(Vector3 pointOfIntersection);

};

#endif // CYLINDER_H