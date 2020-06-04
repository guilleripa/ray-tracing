#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"

using namespace std;

class Object
{
private:
	float refractiveCoefficient;
	float reflectionCoefficient;
	Vector3 color;

public:
	Object();
	Object(float refractiveCoefficient, float reflectionCoefficient, Vector3 color);

	float getRefractiveCoefficient();
	float getReflectionCoefficient();
	Vector3 getColor();

	void setRefractiveCoefficient(float);
	void setReflectionCoefficient(float);
	void setColor(Vector3 color);

	virtual bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float distance, Vector3 pointOfIntersection) const = 0;
	virtual Vector3 getNormalIn(Vector3 pointOfIntersection) const = 0;

};

#endif // OBJECT_H