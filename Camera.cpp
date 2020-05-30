#include "Camera.h"

Camera::Camera(float eye[], float center[], float up[])
{
	this->eye[0] = eye[0];
	this->eye[1] = eye[1];
	this->eye[2] = eye[2];

	this->center[0] = center[0];
	this->center[1] = center[1];
	this->center[2] = center[2];

	this->up[0] = up[0];
	this->up[1] = up[1];
	this->up[2] = up[2];

}

Camera::Camera()
{}

Camera::~Camera()
{}

float* Camera::getEye() {
	return eye;
}

float* Camera::getCenter() {
	return center;
}

float* Camera::getUp() {
	return up;
}

void Camera::setEye(float eye[]) {
	this->eye[0] = eye[0];
	this->eye[1] = eye[1];
	this->eye[2] = eye[2];
}

void Camera::setCenter(float center[]) {
	this->center[0] = center[0];
	this->center[1] = center[1];
	this->center[2] = center[2];
}

void Camera::setUp(float up[]) {
	this->up[0] = up[0];
	this->up[1] = up[1];
	this->up[2] = up[2];
}
