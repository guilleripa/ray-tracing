#include "Object.h"

Object::Object()
{
}

Object::Object(float refractiveCoefficient, float reflectionCoefficient){
	this->refractiveCoefficient = refractiveCoefficient;
	this->reflectionCoefficient = reflectionCoefficient;
}

float Object::getRefractiveCoefficient() {
	return this->refractiveCoefficient;
}

float Object::getReflectionCoefficient() {
	return this->reflectionCoefficient;
}

void Object::setRefractiveCoefficient(float refractiveCoefficient) {
	this->refractiveCoefficient = refractiveCoefficient;
}

void Object::setReflectionCoefficient(float reflectionCoefficient) {
	this->reflectionCoefficient = reflectionCoefficient;
}