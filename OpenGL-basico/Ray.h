#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

using namespace std;

class Ray
{
private:
	Vector3 origin;
	Vector3 direction;
public:
	Ray();
	Ray(Vector3, Vector3);
	~Ray();

	Vector3 getOrigin();
	Vector3 getDirection();
	void setOrigin(Vector3);
	void setDirection(Vector3);

};

#endif // RAY_H