#ifndef CAMERA_H
#define CAMERA_H

using namespace std;

class Camera
{
private:
	float eye[3] = { 0 };
	float center[3] = { 0 };
	float up[3] = { 0 };

public:
	Camera();
	Camera(float eye[], float center[], float up[]);
	~Camera();

	float* getEye();
	float* getCenter();
	float* getUp();
	void setEye(float[]);
	void setCenter(float[]);
	void setUp(float[]);

};

#endif // CAMERA_H