#include "Vector3.h"
#include <cmath>

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

float Vector3::mod() {
    return abs(sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Vector3 Vector3::normalize() {
    return *this / this->mod();
}

Vector3 Vector3::operator*(float k)
{
    return Vector3(this->getX() * k, this->getY() * k, this->getZ() * k);
}

Vector3 Vector3::operator*(Vector3 k)
{
    return Vector3(this->getX() * k.getX(), this->getY() * k.getY(), this->getZ() * k.getZ());
}

Vector3 Vector3::operator/(float k) {
    return *this * (1.0 / k);
}

Vector3 Vector3::operator-(Vector3 v)
{
    return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

Vector3 Vector3::operator+(Vector3 v)
{
    return Vector3(this->getX() + v.getX(), this->getY() + v.getY(), this->getZ() + v.getZ());
}

Vector3 Vector3::cross(Vector3 v)
{
    return Vector3(this->getY() * v.getZ() - this->getZ() * v.getY(),
        this->getZ() * v.getX() - this->getX() * v.getZ(),
        this->getX() * v.getY() - this->getY() * v.getX());
}