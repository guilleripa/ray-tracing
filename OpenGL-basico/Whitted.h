#ifndef WHITTED_H
#define WHITTED_H

#include "Scene.h"

using namespace std;

class Whitted
{
private:

public:
	void run(Scene scene);
	Vector3 trace(Scene scene, Vector3 rayOrigin, Vector3 rayDirection, int depth);
	Vector3 shadow(Scene scene, Object* object, Vector3 rayOrigin, Vector3 rayDirection, Vector3 intersection, Vector3 normal, int depth);
	Object* intersection(Scene scene, Vector3 rayOrigin, Vector3 rayDirection);
};

#endif // WHITTED_H