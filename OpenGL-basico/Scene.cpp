#include "Scene.h"

#include "../Light.h"
#include "Whitted.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Cylinder.h"
#include "Plane.h"
#include <string>


Scene::Scene()
{}


Scene::Scene(int width, int height, int maxDepth, bool parallel, Vector3 backgroundColor){
	this->width = width;
	this->height = height;
	this->maxDepth = maxDepth;
	this->backgroundColor = backgroundColor;
	this->parallel = parallel;
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

Camera* Scene::getCamera() {
	return camera;
}

bool Scene::getParallelism() {
	return parallel;
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

void Scene::setCamera(Camera* camera) {
	this->camera = camera;
}

Scene Scene::loadScene() {
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLError error = doc.LoadFile("../Escena/Scene.xml");

	if (error != 0) throw 6;

	tinyxml2::XMLElement* sceneNode = doc.FirstChildElement("Scene");
	int width = atoi(sceneNode->FindAttribute("width")->Value());
	int height = atoi(sceneNode->FindAttribute("height")->Value());
	int maxDepth = atoi(sceneNode->FindAttribute("maxDepth")->Value());
	string parallel = sceneNode->FindAttribute("parallel")->Value();
	tinyxml2::XMLElement* backgroundColorNode = sceneNode->FirstChildElement("BackgroundColor");
	Scene scene = Scene(
		width, height, maxDepth, parallel == "true",
		Vector3(atof(backgroundColorNode->FindAttribute("x")->Value()),
			atof(backgroundColorNode->FindAttribute("y")->Value()),
			atof(backgroundColorNode->FindAttribute("z")->Value()))
	);

	// camara
	tinyxml2::XMLElement* cameraNode = sceneNode->FirstChildElement("Camera");
	int fov = atof(cameraNode->FindAttribute("fov")->Value());
	int nearDistance = atof(cameraNode->FindAttribute("nearDistance")->Value());
	tinyxml2::XMLElement* eyeNode = cameraNode->FirstChildElement("eye");
	tinyxml2::XMLElement* povNode = cameraNode->FirstChildElement("pov");
	tinyxml2::XMLElement* upNode = cameraNode->FirstChildElement("up");
	Vector3 eye = Vector3(atof(eyeNode->FindAttribute("x")->Value()), atof(eyeNode->FindAttribute("y")->Value()), atof(eyeNode->FindAttribute("z")->Value()));
	Vector3 pov = Vector3(atof(povNode->FindAttribute("x")->Value()), atof(povNode->FindAttribute("y")->Value()), atof(povNode->FindAttribute("z")->Value()));
	Vector3 up = Vector3(atof(upNode->FindAttribute("x")->Value()), atof(upNode->FindAttribute("y")->Value()), atof(upNode->FindAttribute("z")->Value()));
	scene.setCamera(new Camera(fov, nearDistance, eye, pov, up));

	//luces
	vector<Light> lights;
	tinyxml2::XMLElement* lightsNode = sceneNode->FirstChildElement("Lights");
	for (tinyxml2::XMLElement* lightNode = lightsNode->FirstChildElement("Ligth"); lightNode != 0; lightNode = lightNode->NextSiblingElement()) {
		tinyxml2::XMLElement* positionNode = lightNode->FirstChildElement("position");
		tinyxml2::XMLElement* colorNode = lightNode->FirstChildElement("color");
		Vector3 position = Vector3(atof(positionNode->FindAttribute("x")->Value()), atof(positionNode->FindAttribute("y")->Value()), atof(positionNode->FindAttribute("z")->Value()));
		Vector3 color = Vector3(atof(colorNode->FindAttribute("R")->Value()), atof(colorNode->FindAttribute("G")->Value()), atof(colorNode->FindAttribute("B")->Value()));
		lights.push_back(Light(position, color));
	}
	scene.setLights(lights);

	//objetos
	vector<Object*> objects;
	tinyxml2::XMLElement* objectsNode = sceneNode->FirstChildElement("Objects");
	for (tinyxml2::XMLElement* objectNode = objectsNode->FirstChildElement("Object"); objectNode != 0; objectNode = objectNode->NextSiblingElement()) {
		float ambienceCoefficient = atof(objectNode->FindAttribute("ambienceCoefficient")->Value());
		float transmissionCoefficient = atof(objectNode->FindAttribute("transmissionCoefficient")->Value());
		float speculateCoefficient = atof(objectNode->FindAttribute("speculateCoefficient")->Value());
		float diffuseCoefficient = atof(objectNode->FindAttribute("diffuseCoefficient")->Value());
		float indexRefraction = atof(objectNode->FindAttribute("indexRefraction")->Value());

		tinyxml2::XMLElement* colorNode = objectNode->FirstChildElement("color");
		Vector3 color = Vector3(atof(colorNode->FindAttribute("R")->Value()), atof(colorNode->FindAttribute("G")->Value()), atof(colorNode->FindAttribute("B")->Value()));

		string type = objectNode->FindAttribute("type")->Value();
		if (type == "Sphere") {
			float radius = atof(objectNode->FindAttribute("radius")->Value());

			tinyxml2::XMLElement* centerNode = objectNode->FirstChildElement("center");
			Vector3 center = Vector3(atof(centerNode->FindAttribute("x")->Value()), atof(centerNode->FindAttribute("y")->Value()), atof(centerNode->FindAttribute("z")->Value()));
			objects.push_back(new Sphere(center, radius, ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color));
		}
		else if (type == "Triangle") {
			vector<tinyxml2::XMLElement *> tiny_vertices;
			tiny_vertices.push_back(objectNode->FirstChildElement("v0"));
			tiny_vertices.push_back(objectNode->FirstChildElement("v1"));
			tiny_vertices.push_back(objectNode->FirstChildElement("v2"));

			vector<Vector3> vertices;
			for (tinyxml2::XMLElement *vertex : tiny_vertices)
			{
				vertices.push_back(
					Vector3(
						atof(vertex->FindAttribute("x")->Value()),
						atof(vertex->FindAttribute("y")->Value()),
						atof(vertex->FindAttribute("z")->Value())));
			}
			objects.push_back(new Triangle(
				vertices[0], vertices[1], vertices[2],
				ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color));
		}
		else if (type == "Cylinder") {
			float radius = atof(objectNode->FindAttribute("radius")->Value());
			tinyxml2::XMLElement* baseCenterTiny1 = objectNode->FirstChildElement("baseCenter1");
			Vector3 baseCenter1 = Vector3(atof(baseCenterTiny1->FindAttribute("x")->Value()), atof(baseCenterTiny1->FindAttribute("y")->Value()), atof(baseCenterTiny1->FindAttribute("z")->Value()));
			tinyxml2::XMLElement* baseCenterTiny2 = objectNode->FirstChildElement("baseCenter2");
			Vector3 baseCenter2 = Vector3(atof(baseCenterTiny2->FindAttribute("x")->Value()), atof(baseCenterTiny2->FindAttribute("y")->Value()), atof(baseCenterTiny2->FindAttribute("z")->Value()));
			objects.push_back(new Cylinder(baseCenter1, baseCenter2, radius, ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color));

		}
		else if (type == "Plane") {
			tinyxml2::XMLElement* tinyPlanePoint = objectNode->FirstChildElement("planePoint");
			Vector3 planePoint = Vector3(atof(tinyPlanePoint->FindAttribute("x")->Value()), atof(tinyPlanePoint->FindAttribute("y")->Value()), atof(tinyPlanePoint->FindAttribute("z")->Value()));
			tinyxml2::XMLElement* tinyNormal = objectNode->FirstChildElement("normal");
			Vector3 normal = Vector3(atof(tinyNormal->FindAttribute("x")->Value()), atof(tinyNormal->FindAttribute("y")->Value()), atof(tinyNormal->FindAttribute("z")->Value()));
			objects.push_back(new Plane(planePoint, normal, ambienceCoefficient, transmissionCoefficient, speculateCoefficient, diffuseCoefficient, indexRefraction, color));
		}
	}
	scene.setObjects(objects);

	return scene;
}
