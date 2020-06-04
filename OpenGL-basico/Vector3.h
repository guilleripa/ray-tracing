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
    float dot(Vector3 v);
    float mod();
    Vector3 normalize();
    Vector3 operator/(float k);
    Vector3 operator*(float k);
    Vector3 operator-(Vector3 v);
    Vector3 operator+(Vector3 v);
    Vector3 cross(Vector3 v);
};

#endif // VECTOR_H