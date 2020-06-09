#include "Camera.h"

Camera::Camera(Vector3 eye, Vector3 pov, Vector3 up)
{
	this->eye = eye;
	this->pov = pov;
	this->up = up;

}

Camera::Camera()
{}

Camera::~Camera()
{}

Vector3 Camera::getEye() {
	return eye;
}

Vector3 Camera::getPov() {
	return pov;
}

Vector3 Camera::getUp() {
	return up;
}

void Camera::setEye(Vector3 eye) {
	this->eye = eye;
}

void Camera::setPov(Vector3 pov) {
	this->pov = pov;
}

void Camera::setUp(Vector3 up) {
	this->up = up;
}
