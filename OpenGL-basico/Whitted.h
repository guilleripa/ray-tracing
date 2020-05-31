#ifndef WHITTED_H
#define WHITTED_H

#include "Scene.h"

using namespace std;

class Whitted
{
private:

public:
	void run(Scene scene);
	Vector3 trace(Scene scene, Vector3 origin, Vector3 direction, int depth);
	Vector3 shadow(Scene scene, int depth);
};

#endif // WHITTED_H