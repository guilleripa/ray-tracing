#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction)
{
	this->origin = origin;
	this->direction = direction;
}

Ray::~Ray()
{}

Ray::Ray()
{}

Vector3 Ray::getOrigin() {
	return origin;
}

Vector3 Ray::getDirection() {
	return direction;
}

void Ray::setOrigin(Vector3 origin) {
	this->origin = origin;
}

void Ray::setDirection(Vector3 direction) {
	this->direction = direction;
}

