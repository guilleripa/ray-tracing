#include "Sphere.h"

Sphere::Sphere()
{}

Sphere::Sphere(Vector3 center, float radius) {
	this->center = center;
	this->radius = radius;
}

Vector3 Sphere::getCenter() {
	return this->center;
}

float Sphere::getRadius() {
	return this->radius;
}

bool Sphere::intersects(Vector3 rayOrigin, Vector3 rayDirection, float distance) {
	return false;
}