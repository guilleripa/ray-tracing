#ifndef OBJECT_H
#define OBJECT_H

using namespace std;

class Object
{
private:
	float refractiveCoefficient;
	float reflectionCoefficient;

public:
	Object();

	float getRefractiveCoefficient();
	float getReflectionCoefficient();

	void setRefractiveCoefficient(float);
	void setReflectionCoefficient(float);

};

#endif // OBJECT_H