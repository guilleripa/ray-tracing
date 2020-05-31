#include "Scene.h"

Scene::Scene()
{}

int Scene::getWidth() {
	return width;
}

int Scene::getHeight() {
	return height;
}

void Scene::setWidth(int width) {
	this->width = width;
}

void Scene::setHeight(int height) {
	this->height = height;
}

Vector3 Scene::getBackgroundColor() {
	return backgroundColor;
}

void Scene::setBackgroundColor(Vector3 backgroundColor) {
	this->backgroundColor = backgroundColor;
}