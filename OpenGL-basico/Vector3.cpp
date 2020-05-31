#include "Vector3.h"


Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::~Vector3()
{}

float Vector3::getX() {
    return this->x;
}

float Vector3::getY() {
    return this->y;
}

float Vector3::getZ() {
    return this->z;
}

void Vector3::setX(float x) {
    this->x = x;
}

void Vector3::setY(float y) {
    this->y = y;
}

void Vector3::setZ(float z) {
    this->z = z;
}

float Vector3::dot(Vector3 v)
{
    return this->x * v.x +
        this->y * v.y +
        this->z * v.z;
}