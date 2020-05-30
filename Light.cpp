#include "Light.h"

Light::Light(float position[], float color[])
{
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	this->position[3] = position[3];

	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
	this->color[3] = color[3];

}

Light::~Light()
{}

Light::Light()
{}

float* Light::getColor() {
	return color;
}

float* Light::getPosition() {
	return position;
}

void Light::setPosition(float position[]) {
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	this->position[3] = position[3];
}

void Light::setColor(float color[]) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
	this->color[3] = color[3];
}

