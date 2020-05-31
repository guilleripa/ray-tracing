#ifndef SCENE_H
#define SCENE_H

#include "Vector3.h"

using namespace std;

class Scene
{
private:
	int width = 640;
	int height = 400;
	Vector3 backgroundColor = Vector3(255, 0, 0);

public:
	Scene();

	int getWidth();
	int getHeight();
	Vector3 getBackgroundColor();

	void setWidth(int);
	void setHeight(int);
	void setBackgroundColor(Vector3);
};

#endif // SCENE_H