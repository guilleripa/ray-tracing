#ifndef LIGHT_H
#define LIGHT_H

using namespace std;

class Light
{
private:
	float position[4] = { 0 };
	float color[4] = { 0 };
public:
	Light();
	Light(float[], float[]);
	~Light();

	float* getPosition();
	float* getColor();
	void setPosition(float[]);
	void setColor(float[]);

};

#endif // LIGHT_H