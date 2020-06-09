#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Vector3.h"
#include "Object.h"
#include "../Light.h"
#include "../Camera.h"
#include "../tinyxml2.h"

using namespace std;

class Scene
{
private:
	int width = 640;
	int height = 480;
	int maxDepth = 4;
	Vector3 backgroundColor = Vector3(0, 0, 0);
	vector<Object*> objects;
	vector<Light> lights;
	Camera* camera;

public:
	Scene();
	Scene(int width, int height, int maxDepth, Vector3 backgroundColor);

	int getWidth();
	int getHeight();
	int getMaxDepth();

	Vector3 getBackgroundColor();
	vector<Object*> getObjects();
	vector<Light> getLights();
	Camera* getCamera();

	Scene loadScene();

	void setWidth(int);
	void setHeight(int);
	void setMaxDepth(int);
	void setBackgroundColor(Vector3);
	void setObjects(vector<Object*>);
	void setLights(vector<Light>);
	void setCamera(Camera*);
};

#endif // SCENE_H