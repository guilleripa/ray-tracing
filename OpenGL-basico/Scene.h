#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Vector3.h"
#include "Object.h"
#include "../Light.h"
#include "../Camera.h"

using namespace std;

class Scene
{
private:
	int width = 640;
	int height = 400;
	int maxDepth = 4;
	Vector3 backgroundColor = Vector3(255, 0, 0);
	Object* objects;
	vector<Light> lights;
	Camera camera;

public:
	Scene();

	int getWidth();
	int getHeight();
	int getMaxDepth();
	Vector3 getBackgroundColor();
	vector<Light> getLight();

	void setWidth(int);
	void setHeight(int);
	void setMaxDepth(int);
	void setBackgroundColor(Vector3);
};

#endif // SCENE_H