#include "Scene.h"

#include "../Light.h"
#include "Whitted.h"
#include "Sphere.h"
#include <string>

Scene::Scene()
{}


Scene::Scene(int width, int height, int maxDepth, Vector3 backgroundColor){
	this->width = width;
	this->height = height;
	this->maxDepth = maxDepth;
	this->backgroundColor = backgroundColor;
}

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

void Scene::setObjects(vector<Object*> objects) {
	this->objects = objects;
}

void Scene::setLights(vector<Light> lights) {
	this->lights = lights;
}

void Scene::setCamera(Camera camera) {
	this->camera = camera;
}

Scene Scene::loadScene() {
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLError error = doc.LoadFile("../OpenGL-basico/Scene.xml");

	if (error != 0) throw ;

	tinyxml2::XMLElement* sceneNode = doc.FirstChildElement("Scene");
	int width = atoi(sceneNode->FindAttribute("width")->Value());
	int height = atoi(sceneNode->FindAttribute("height")->Value());
	int maxDepth = atoi(sceneNode->FindAttribute("maxDepth")->Value());
	tinyxml2::XMLElement* backgroundColorNode = sceneNode->FirstChildElement("BackgroundColor");
	Scene scene = Scene(
		width, height, maxDepth, 
		Vector3(atoi(backgroundColorNode->FindAttribute("x")->Value()), 
			atoi(backgroundColorNode->FindAttribute("y")->Value()), 
			atoi(backgroundColorNode->FindAttribute("z")->Value()))
	);

	// camara
	tinyxml2::XMLElement* cameraNode = sceneNode->FirstChildElement("Camera");
	int fov = atoi(cameraNode->FindAttribute("fov")->Value());
	int nearDistance = atoi(cameraNode->FindAttribute("nearDistance")->Value());
	tinyxml2::XMLElement* eyeNode = cameraNode->FirstChildElement("eye");
	tinyxml2::XMLElement* povNode = cameraNode->FirstChildElement("pov");
	tinyxml2::XMLElement* upNode = cameraNode->FirstChildElement("up");
	Vector3 eye = Vector3(atoi(eyeNode->FindAttribute("x")->Value()), atoi(eyeNode->FindAttribute("y")->Value()), atoi(eyeNode->FindAttribute("z")->Value()));
	Vector3 pov = Vector3(atoi(povNode->FindAttribute("x")->Value()), atoi(povNode->FindAttribute("y")->Value()), atoi(povNode->FindAttribute("z")->Value()));
	Vector3 up = Vector3(atoi(upNode->FindAttribute("x")->Value()), atoi(upNode->FindAttribute("y")->Value()), atoi(upNode->FindAttribute("z")->Value()));
	scene.setCamera(Camera(fov, nearDistance, eye, pov, up));

	//luces
	vector<Light> lights;
	tinyxml2::XMLElement* lightsNode = sceneNode->FirstChildElement("Lights");
	for (tinyxml2::XMLElement* lightNode = lightsNode->FirstChildElement("Ligth"); lightNode != 0; lightNode = lightNode->NextSiblingElement()) {
		tinyxml2::XMLElement* positionNode = lightNode->FirstChildElement("position");
		tinyxml2::XMLElement* colorNode = lightNode->FirstChildElement("color");
		Vector3 position = Vector3(atoi(positionNode->FindAttribute("x")->Value()), atoi(positionNode->FindAttribute("y")->Value()), atoi(positionNode->FindAttribute("z")->Value()));
		Vector3 color = Vector3(atoi(colorNode->FindAttribute("x")->Value()), atoi(colorNode->FindAttribute("y")->Value()), atoi(colorNode->FindAttribute("z")->Value()));
		lights.push_back(Light(position, color));
	}
	scene.setLights(lights);

	//objetos
	vector<Object*> objects;
	tinyxml2::XMLElement* objectsNode = sceneNode->FirstChildElement("Objects");
	for (tinyxml2::XMLElement* objectNode = objectsNode->FirstChildElement("Object"); objectNode != 0; objectNode = objectNode->NextSiblingElement()) {
		string type = objectNode->FindAttribute("type")->Value();
		if (type == "Sphere") {
			float radius = atof(objectNode->FindAttribute("radius")->Value());
			float ambienceCoefficient = atof(objectNode->FindAttribute("ambienceCoefficient")->Value());
			float transmissionCoefficient = atof(objectNode->FindAttribute("transmissionCoefficient")->Value());
			float speculateCoefficient = atof(objectNode->FindAttribute("speculateCoefficient")->Value());
			float diffuseCoefficient = atof(objectNode->FindAttribute("diffuseCoefficient")->Value());
			float indexRefraction = atof(objectNode->FindAttribute("indexRefraction")->Value());

			tinyxml2::XMLElement* centerNode = objectNode->FirstChildElement("center");
			tinyxml2::XMLElement* colorNode = objectNode->FirstChildElement("color");
			Vector3 center = Vector3(atoi(centerNode->FindAttribute("x")->Value()), atoi(centerNode->FindAttribute("y")->Value()), atoi(centerNode->FindAttribute("z")->Value()));
			Vector3 color = Vector3(atoi(colorNode->FindAttribute("x")->Value()), atoi(colorNode->FindAttribute("y")->Value()), atoi(colorNode->FindAttribute("z")->Value()));
			objects.push_back(new Sphere(center, radius, ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color));
		}
	}
	scene.setObjects(objects);

	return scene;
}
