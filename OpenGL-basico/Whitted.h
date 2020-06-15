#ifndef WHITTED_H
#define WHITTED_H

#include "Scene.h"
#include <stack>

using namespace std;

class Whitted
{
private:

public:
	void run(Scene scene);
	vector<Vector3> trace(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, int depth, std::stack<Object*> intersectedObjectsStack);
	Vector3 shadow(Scene scene, Object* object, Vector3 rayOrigin, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth, std::stack<Object*> intersectedObjectsStack);
	Vector3 speculateColor(Vector3 rayLightDirection, Vector3 rayDirection, Vector3 normal, Vector3 lightColor, Vector3 speculateFactor);
	Vector3 reflectColor(Scene scene, Object* object, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth, std::stack<Object*> intersectedObjectsStack);
	Vector3 refractColor(Scene scene, Object* object, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth, std::stack<Object*> intersectedObjectsStack);
	Object* intersection(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, Vector3* nearestPointOfIntersection );
	Vector3 reflect(Vector3 rayIncident, Vector3 normal);
	Vector3 refract(Vector3 rayIncident, Vector3 normal, float eta);
};

#endif // WHITTED_H