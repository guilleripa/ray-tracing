#include "Object.h"

Object::Object()
{
}

Object::Object(float refractiveCoefficient, float reflectionCoefficient, Vector3 color){
	this->refractiveCoefficient = refractiveCoefficient;
	this->reflectionCoefficient = reflectionCoefficient;
	this->color = color;
}

float Object::getRefractiveCoefficient() {
	return this->refractiveCoefficient;
}

float Object::getReflectionCoefficient() {
	return this->reflectionCoefficient;
}

Vector3 Object::getColor() {
	return this->color;
}

void Object::setRefractiveCoefficient(float refractiveCoefficient) {
	this->refractiveCoefficient = refractiveCoefficient;
}

void Object::setReflectionCoefficient(float reflectionCoefficient) {
	this->reflectionCoefficient = reflectionCoefficient;
}

void Object::setColor(Vector3 color) {
	this->color = color;
}