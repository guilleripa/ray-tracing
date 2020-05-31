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

Vector3 Scene::getBackgroundColor() {
	return backgroundColor;
}

vector<Light> Scene::getLight() {
	return lights;
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