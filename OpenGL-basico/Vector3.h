#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

class Vector3
{
private:
	float x, y, z;
public:
    Vector3();
    Vector3(float x, float y, float z);
    virtual ~Vector3();
    float getX();
    float getY();
    float getZ();
    void setX(float);
    void setY(float);
    void setZ(float);
    float Vector3::dot(Vector3 v);
};

#endif // VECTOR_H