#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"

using namespace std;

class Object
{
private:
	float refractiveCoefficient;
	float reflectionCoefficient;

public:
	Object();
	Object(float refractiveCoefficient, float reflectionCoefficient);

	float getRefractiveCoefficient();
	float getReflectionCoefficient();

	void setRefractiveCoefficient(float);
	void setReflectionCoefficient(float);

	virtual bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float distance) const = 0;

};

#endif // OBJECT_H