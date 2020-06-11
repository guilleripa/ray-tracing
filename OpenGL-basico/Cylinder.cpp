#include "Cylinder.h"

#include <cmath>
#include <limits>

using namespace std;

Cylinder::Cylinder(Vector3 baseCenter1, Vector3 baseCenter2, float radius, float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color)
	: Object(ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color) {
	this->baseCenter1 = baseCenter1;
	this->baseCenter2 = baseCenter2;
	this->radius = radius;
}

bool Cylinder::intersectBase(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection, Vector3 baseCenter) {
	Vector3 dir = (baseCenter2 - baseCenter1).normalize();

	float dotProd = dir.dot(rayDirection);
	// Parallel
	if (dotProd < 0.00001 && dotProd > -0.00001) {
		return false;
	}

	float aux = dir.dot(baseCenter - rayOrigin) / dotProd;
	if (aux < 0.001) {
		return false;
	}

	Vector3 intersect = rayOrigin + (rayDirection * aux);

	float distToCenter = (intersect - baseCenter).mod();

	if (distToCenter < radius) {
		*distance = distToCenter;
		*pointOfIntersection = intersect;
		return true;
	}

	return false;
}

bool Cylinder::intersectBody(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection) {
	Vector3	cylinderDir = baseCenter2 - baseCenter1;
	float height = cylinderDir.mod();
	cylinderDir = cylinderDir.normalize();

	float directionsDot = rayDirection.dot(cylinderDir);
	Vector3 baseToOrigin = rayOrigin - baseCenter1;

	float a = 1 - directionsDot * directionsDot;
	float b = 2 * (baseToOrigin.dot(rayDirection) - directionsDot * baseToOrigin.dot(cylinderDir));
	float c = baseToOrigin.dot(baseToOrigin) - baseToOrigin.dot(cylinderDir) * baseToOrigin.dot(cylinderDir) - radius * radius;
	float delta = b * b - 4 * a * c;

	if (delta < 0.001) {
		return false;
	}

	float root1 = (-b - sqrt(delta)) / (2 * a);
	float root2 = (-b + sqrt(delta)) / (2 * a);

	if (root2 < 0.001) {
		return false;
	}

	float projectCenter = baseCenter1.dot(cylinderDir);

	Vector3 intersect1 = rayOrigin + (rayDirection * root1);
	float projectIntersect1 = intersect1.dot(cylinderDir);
	if (root1 >= 0.001 && projectIntersect1 > projectCenter && projectIntersect1 < projectCenter + height) {
		*distance = root1;
		*pointOfIntersection = intersect1;
		return true;
	}

	Vector3 intersect2 = rayOrigin + (rayDirection * root2);
	float projectIntersect2 = intersect2.dot(cylinderDir);
	if (root2 >= 0.001 && projectIntersect2 > projectCenter && projectIntersect2 < projectCenter + height) {
		*distance = root2;
		*pointOfIntersection = intersect2;
		return true;
	}

	return false;

}

bool Cylinder::intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection) {
	Vector3 pointOfIntB1, pointOfIntB2, pointOfIntBody;
	float distB1, distB2, distBody;
	bool interB1 = intersectBase(rayOrigin, rayDirection, &distB1, &pointOfIntB1, baseCenter1);
	bool interB2 = intersectBase(rayOrigin, rayDirection, &distB2, &pointOfIntB2, baseCenter2);
	bool interBody = intersectBody(rayOrigin, rayDirection, &distBody, &pointOfIntBody);

	*distance = numeric_limits<float>::infinity();
	if (interB1 && distB1 < *distance){
		*distance = distB1;
		*pointOfIntersection = pointOfIntB1;
	}
	if (interB2 && distB2 < *distance) {
		*distance = distB2;
		*pointOfIntersection = pointOfIntB2;
	}
	if (interBody && distBody < *distance) {
		*distance = distBody;
		*pointOfIntersection = pointOfIntBody;
	}
	return interB1 || interB2 || interBody;
}

Vector3 Cylinder::getNormalIn(Vector3 pointOfIntersection) {
	Vector3 vec1 = pointOfIntersection - baseCenter1;
	Vector3 vec2 = pointOfIntersection - baseCenter2;
	Vector3 dir = baseCenter2 - baseCenter1;
	dir = dir.normalize();

	if (vec1.dot(dir) < 0.001 && vec1.dot(dir) > -0.001) {
		return dir;
	}

	if (vec2.dot(dir) < 0.001 && vec2.dot(dir) > -0.001) {
		return dir * -1;
	}

	Vector3 interToBase = baseCenter1 - pointOfIntersection;
	Vector3 res = interToBase - dir * interToBase.dot(dir);
	return res.normalize();
}