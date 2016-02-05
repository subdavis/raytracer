#ifndef CAMERA_H
#define CAMERA_H
#include "Vector3.h"

class Ray
{
public:
    Ray();
    Ray(Vector3 point, Vector3 direction);
    ~Ray();
    Vector3 point;
    Vector3 d;

};

#endif // CAMERA_H
