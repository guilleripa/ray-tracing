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
	float ambientLight = 0.2;
	Vector3 backgroundColor = Vector3(0, 0, 0);
	vector<Object*> objects;
	vector<Light> lights;
	Camera camera;

public:
	Scene();

	int getWidth();
	int getHeight();
	int getMaxDepth();
	float getAmbientLight();
	Vector3 getBackgroundColor();
	vector<Object*> getObjects();
	vector<Light> getLights();
	Camera getCamera();

	void setWidth(int);
	void setHeight(int);
	void setMaxDepth(int);
	void setBackgroundColor(Vector3);
	void setObjects(vector<Object*>);
	void setLights(vector<Light>);
	void setCamera(Camera);
};

#endif // SCENE_H