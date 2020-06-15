#include "Plane.h"
#include <cmath>
#include <vector>


Plane::Plane() {}

Plane::Plane(Vector3 planePoint, Vector3 normal, float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color)
	: Object(ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color) {
	this->planePoint = planePoint;
	this->normal = normal;
}


Vector3 Plane::getNormalIn(Vector3 placeholder){
    return this->normal;
}

bool Plane::intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection){
    Vector3 normal = getNormalIn(planePoint);

	// The Ray and the Plane are parallel
	float dirProyection = normal.dot(rayDirection);
	if (abs(dirProyection) < ZERO) {
		return false;
	}

	// distance from origin to plane
	float D = -normal.dot(planePoint);
	*distance = (-normal.dot(rayOrigin) + D) / dirProyection;

	// The Plane Is "Behind" The Ray
	if (*distance < ZERO) {
		return false;
	}

	*pointOfIntersection = rayOrigin + (rayDirection * (*distance));

	return true;
}
