#include "Object.h"

Object::Object()
{
	this->initialized = false;
}

Object::Object(float refractiveCoefficient, float reflectionCoefficient){
	this->initialized = true;
	this->refractiveCoefficient = refractiveCoefficient;
	this->reflectionCoefficient = reflectionCoefficient;
}

float Object::getRefractiveCoefficient() {
	return this->refractiveCoefficient;
}

float Object::getReflectionCoefficient() {
	return this->reflectionCoefficient;
}

bool Object::getInitialized() {
	return this->initialized;
}

void Object::setRefractiveCoefficient(float refractiveCoefficient) {
	this->refractiveCoefficient = refractiveCoefficient;
}

void Object::setReflectionCoefficient(float reflectionCoefficient) {
	this->reflectionCoefficient = reflectionCoefficient;
}