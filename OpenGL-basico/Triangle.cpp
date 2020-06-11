#include "Triangle.h"
#include <iostream>

#include <cmath>
#include <vector>


Triangle::Triangle() {}

Triangle::Triangle(Vector3 v0, Vector3 v1, Vector3 v2, float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color)
	: Object(ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color) {
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
}

Vector3 Triangle::getNormalIn(Vector3 placeholder) {
	Vector3 aux1 = v1 - v0;
	Vector3 aux2 = v2 - v0;
	return aux1.cross(aux2).normalize()*-1;
}

bool Triangle::pointInTriangle(Vector3 pointOfIntersection) {
	Vector3 normal = getNormalIn(v0);
	Vector3 C; // perpendicular vector to triangle's plane

	// edge 0
	Vector3 edge0 = v1 - v0;
	Vector3 vp0 = pointOfIntersection - v0;
	C = edge0.cross(vp0);
	if (normal.dot(C) > ZERO) return false; // pointOfIntersection is on the "right" side

	// edge 1
	Vector3 edge1 = v2 - v1;
	Vector3 vp1 = pointOfIntersection - v1;
	C = edge1.cross(vp1);
	if (normal.dot(C) > ZERO)  return false; // pointOfIntersection is on the "right" side

	// edge 2
	Vector3 edge2 = v0 - v2;
	Vector3 vp2 = pointOfIntersection - v2;
	C = edge2.cross(vp2);
	if (normal.dot(C) > ZERO) return false; // pointOfIntersection is on the "right" side;

	return true; // this ray hits the triangle
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/
// /ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
bool Triangle::intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection) {
	Vector3 normal = getNormalIn(v1);

	// The Ray And The Triangle Are Parallel
	float dirProyection = normal.dot(rayDirection);
	if (abs(dirProyection) < ZERO) {
		return false;
	}

	// distance from origin to plane
	float D = -normal.dot(v0);
	*distance = (-normal.dot(rayOrigin) + D) / dirProyection;

	// The Triangle Is "Behind" The Ray
	if (*distance < ZERO) {
		return false;
	}

	*pointOfIntersection = rayOrigin + (rayDirection * (*distance));
	bool inside = pointInTriangle(*pointOfIntersection);

	//cout << "distance: " << *distance << " " << "inside: " << inside << endl;
	return inside;
}
