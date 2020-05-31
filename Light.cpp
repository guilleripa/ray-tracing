#include "Light.h"

Light::Light(Vector3 position, Vector3 color)
{
	this->position = position;
	this->color = color;
}

Light::~Light()
{}

Light::Light()
{}

Vector3 Light::getColor() {
	return color;
}

Vector3 Light::getPosition() {
	return position;
}

void Light::setPosition(Vector3 position) {
	this->position = position;
}

void Light::setColor(Vector3 color) {
	this->color = color;
}

