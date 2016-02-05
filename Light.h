#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h" // Base class: Ray
#include "Ray.h"

class Light : public Ray
{
public:
    Light(Vector3 point, Vector3 direction, Color color);
    ~Light();
    Color color;

};

#endif // LIGHT_H
