#include <iostream>
#include "FreeImage.h"
#include "tinyxml2.h"

#include "Light.h"
#include "OpenGL-basico/Whitted.h"

using namespace std;

int main(int argc, char *argv[]) {
	
	tinyxml2::XMLDocument doc;

	tinyxml2::XMLError error = doc.LoadFile("../OpenGL-basico/Scene.xml");
	if (error != 0) return 1;

	tinyxml2::XMLElement* node1 = doc.FirstChildElement("Scene")->FirstChildElement("Lights")->FirstChildElement("Ligth")->FirstChildElement("position");

	float x = atoi(node1->FindAttribute("x")->Value());

	Vector3 position1 = { x, x, x};
	Vector3 color1 = { x, x, x };

	Light light1 = Light(position1, color1);

	Scene scene = Scene();

	Whitted().run(scene);

	return 0;
}
