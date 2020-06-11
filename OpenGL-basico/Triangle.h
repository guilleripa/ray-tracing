#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "Vector3.h"
#include <vector>

class Triangle : public Object
{
private:
	// for getNormalIn to work we need to define them counter-clockwise.
	Vector3 v0, v1, v2;
public:
	Triangle();
	Triangle(Vector3 v0, Vector3 v1, Vector3 v2, float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color);

	bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection);
	bool pointInTriangle(Vector3 pointofIntersection);
	Vector3 getNormalIn(Vector3 placeholder);

};

#endif // TRIANGLE_H
