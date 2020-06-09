#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3.h"

using namespace std;

#define ZERO 0.0001

class Object
{
private:
	float ambienceCoefficient;
	float transmissionCoefficient;
	float speculateCoefficient;
	float diffuseCoefficient;
	float indexRefraction;
	Vector3 color;

public:
	Object();
	Object(float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color);

	float getAmbienceCoefficient();
	float getTransmissionCoefficient();
	float getSpeculateCoefficient();
	float getDiffuseCoefficient();
	float getIndexRefraction();
	Vector3 getColor();

	void setAmbienceCoefficient(float);
	void setTransmissionCoefficient(float);
	void setSpeculateCoefficient(float);
	void setDiffuseCoefficient(float);
	void setIndexRefraction(float);
	void setColor(Vector3 color);

	virtual bool intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection) = 0;
	virtual Vector3 getNormalIn(Vector3 pointOfIntersection) = 0;

};

#endif // OBJECT_H