#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Vector3.h"
#include <vector>

class Plane : public Object
{
private:
	Vector3 planePoint, normal;
public:
	Plane();
	Plane(Vector3 planePoint, Vector3 normal, float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color);

	bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection);
	Vector3 getNormalIn(Vector3 placeholder);
};

#endif // PLANE_H
