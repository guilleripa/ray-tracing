#include "Scene.h"

Scene::Scene()
{}

int Scene::getWidth() {
	return width;
}

int Scene::getHeight() {
	return height;
}

int Scene::getMaxDepth() {
	return maxDepth;
}


float Scene::getAmbientLight() {
	return ambientLight;
}

Vector3 Scene::getBackgroundColor() {
	return backgroundColor;
}

vector<Object*> Scene::getObjects() {
	return objects;
}

vector<Light> Scene::getLights() {
	return lights;
}

Camera Scene::getCamera() {
	return camera;
}

void Scene::setWidth(int width) {
	this->width = width;
}

void Scene::setHeight(int height) {
	this->height = height;
}

void Scene::setMaxDepth(int maxDepth) {
	this->maxDepth = maxDepth;
}

void Scene::setBackgroundColor(Vector3 backgroundColor) {
	this->backgroundColor = backgroundColor;
}

void Scene::setCamera(Camera camera) {
	this->camera = camera;
}