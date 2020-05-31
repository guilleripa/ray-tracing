#ifndef LIGHT_H
#define LIGHT_H

#include "OpenGL-basico/Vector3.h"

using namespace std;

class Light
{
private:
	Vector3 position;
	Vector3 color;
public:
	Light();
	Light(Vector3, Vector3);
	~Light();

	Vector3 getPosition();
	Vector3 getColor();
	void setPosition(Vector3);
	void setColor(Vector3);

};

#endif // LIGHT_H