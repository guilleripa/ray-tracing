#include "Camera.h"

Camera::Camera(int fov, int nearDistance, Vector3 eye, Vector3 pov, Vector3 up)
{
	this->fov = fov;
	this->nearDistance = nearDistance;
	this->eye = eye;
	this->pov = pov;
	this->up = up;

}

Camera::Camera()
{}

Camera::~Camera()
{}

int Camera::getFov() {
	return fov;
}

int Camera::getNearDistance() {
	return nearDistance;
}

Vector3 Camera::getEye() {
	return eye;
}

Vector3 Camera::getPov() {
	return pov;
}

Vector3 Camera::getUp() {
	return up;
}

void Camera::setFov(int fov) {
	this->fov = fov;
}

void Camera::setNearDistance(int nearDistance) {
	this->nearDistance = nearDistance;
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
