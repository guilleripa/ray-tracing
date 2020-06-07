#include <iostream>
#include "FreeImage.h"
#include "tinyxml2.h"

#include "Light.h"
#include "OpenGL-basico/Whitted.h"
#include "OpenGL-basico/Sphere.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLError error = doc.LoadFile("../OpenGL-basico/Scene.xml");
	if (error != 0) return 1;

	tinyxml2::XMLElement* node1 = doc.FirstChildElement("Scene")->FirstChildElement("Lights")->FirstChildElement("Ligth")->FirstChildElement("position");

	float x = atoi(node1->FindAttribute("x")->Value());

	Vector3 position1 = { 5, 1, 5};
	Vector3 color1 = { 250, 250, 250 };

	//Vector3 position2 = { -5, 0, 3 };
	//Vector3 color2 = { 255, 255, 255 };

	Light light1 = Light(position1, color1);
	//Light light2 = Light(position1, color1);

	Vector3 eye = Vector3(0, -5, 20);
	Vector3 pov = Vector3(0, 0, 0);
	Vector3 up = Vector3(0, 1, 0);

	Camera camera = Camera(eye, pov, up);

	//coefAmbiente = "0.1" coefTransmision = "0" coefEspecular = "1" coefDifuso = "0"  indiceRefraccion = "0"> < / esfera>
	//coefAmbiente = "0.3" coefTransmision = "0.7" coefEspecular = "0" coefDifuso = "0"  indiceRefraccion = "1.3"> < / esfera>

	Sphere* sphere1 = new Sphere(Vector3(0, 0, 0), 2.0, 0.1, 0.1, 1, 0.1, 0.1, Vector3(0, 100, 255));
	Sphere* sphere2 = new Sphere(Vector3(3, 0, 3), 1.0, 0.1, 0.1, 2, 0.1, 0.1, Vector3(10, 255, 10));
	//Sphere* sphere3 = new Sphere(Vector3(2, 0, 2), 2.0, 0.3, 0.7, 2, 0, 3.0, Vector3(255, 0, 0));

	vector<Object*> objects;
	objects.push_back(sphere1);
	objects.push_back(sphere2);
	//objects.push_back(sphere3);

	vector<Light> lights;
	lights.push_back(light1);
	//lights.push_back(light2);

	Scene scene = Scene();
	scene.setObjects(objects);
	scene.setCamera(camera);
	scene.setLights(lights);
	Whitted().run(scene);

	return 0;
}
