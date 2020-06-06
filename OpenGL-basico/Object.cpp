#include "Object.h"

Object::Object()
{
}

Object::Object(float ambienceCoefficient, float transmissionCoefficient, float speculateCoefficient, float diffuseCoefficient, float indexRefraction, Vector3 color){
	this->ambienceCoefficient = ambienceCoefficient;
	this->transmissionCoefficient = transmissionCoefficient;
	this->speculateCoefficient = speculateCoefficient;
	this->diffuseCoefficient = diffuseCoefficient;
	this->indexRefraction = indexRefraction;
	this->color = color;
}

float Object::getAmbienceCoefficient() {
	return this->ambienceCoefficient;
}

float Object::getTransmissionCoefficient() {
	return this->transmissionCoefficient;
}

float Object::getSpeculateCoefficient() {
	return this->speculateCoefficient;
}


float Object::getDiffuseCoefficient() {
	return this->diffuseCoefficient;
}


float Object::getIndexRefraction() {
	return this->indexRefraction;
}

Vector3 Object::getColor() {
	return this->color;
}

void Object::setColor(Vector3 color) {
	this->color = color;
}