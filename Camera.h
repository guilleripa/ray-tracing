#ifndef CAMERA_H
#define CAMERA_H

#include "OpenGL-basico/Vector3.h"

using namespace std;

class Camera
{
private:
	int fov;
	int nearDistance;
	Vector3 eye;
	Vector3 pov;
	Vector3 up;

public:
	Camera();
	Camera(int fov, int nearDistance, Vector3 eye, Vector3 pov, Vector3 up);
	~Camera();

	int getFov();
	int getNearDistance();
	Vector3 getEye();
	Vector3 getPov();
	Vector3 getUp();

	void setFov(int);
	void setNearDistance(int);
	void setEye(Vector3);
	void setPov(Vector3);
	void setUp(Vector3);

};

#endif // CAMERA_H