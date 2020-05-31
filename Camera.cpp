#include "Camera.h"

Camera::Camera(Vector3 eye, Vector3 center, Vector3 up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;

}

Camera::Camera()
{}

Camera::~Camera()
{}

Vector3 Camera::getEye() {
	return eye;
}

Vector3 Camera::getCenter() {
	return center;
}

Vector3 Camera::getUp() {
	return up;
}

void Camera::setEye(Vector3 eye) {
	this->eye = eye;
}

void Camera::setCenter(Vector3 center) {
	this->center = center;
}

void Camera::setUp(Vector3 up) {
	this->up = up;
}
