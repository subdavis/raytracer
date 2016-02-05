#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h" // Base class: Ray
#include "Vector3.h"

class Light
{
public:
    Light();
    Light(Vector3 point, Color color);
    ~Light();
    Color color;
    Vector3 point;

};

#endif // LIGHT_H
