#include "Sphere.h"
#include <cmath>

Sphere::Sphere()
{}

Sphere::Sphere(Vector3 center, float radius, float refractiveCoefficient, float reflectionCoefficient, Vector3 color) 
	: Object(refractiveCoefficient, reflectionCoefficient, color) {
	this->center = center;
	this->radius = radius;
}

Vector3 Sphere::getCenter() {
	return this->center;
}

float Sphere::getRadius() {
	return this->radius;
}

bool Sphere::intersects(Vector3 rayOrigin, Vector3 rayDirection, float* distance, Vector3* pointOfIntersection) {
	double dirX = rayDirection.getX();
	double dirY = rayDirection.getY();
	double dirZ = rayDirection.getZ();
	double oriX = rayOrigin.getX();
	double oriY = rayOrigin.getY();
	double oriZ = rayOrigin.getZ();

	double a = pow(dirX, 2) + pow(dirY, 2) + pow(dirZ, 2);
	double b = 2 * (dirX * (oriX - center.getX()) + dirY * (oriY - center.getY()) + dirZ * (oriZ - center.getZ()));
	double c = pow(oriX - center.getX(), 2) + pow(oriY - center.getY(), 2) + pow(oriZ - center.getZ(), 2) - pow(radius, 2);
	double delta = b * b - 4 * a * c;

	if (delta < 0) {
		return false; // No hay interseccion
	}

	double root1 = (-b - sqrt(delta)) / (2 * a);
	double root2 = (-b + sqrt(delta)) / (2 * a);

	if (root2 < 0.01) {
		return false; // La esfera esta toda atras de la camara
	}

	if (root1 > 0.01) {
		*pointOfIntersection = rayOrigin + rayDirection * root1;
		*distance = root1;
		return true; // La esfera esta toda adelante de la camara
	} else {
		*pointOfIntersection = rayOrigin + rayDirection * root2;
		*distance = root2;
		return true; // La camara esta adentro de la esfera
	}

	return false;
}

Vector3 Sphere::getNormalIn(Vector3 pointOfIntersection) {
	return (center - pointOfIntersection).normalize();
}
