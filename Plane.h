#ifndef PLANE_H
#define PLANE_H

#include "Drawable.h" // Base class: Drawable
#include "Vector3.h"
#include "Color.h"

class Plane : public Drawable
{
public:
    Plane() {}
    Plane(Vector3 point, Vector3 ortho, Color c);
    double intersect(Ray *r);
    ~Plane();
    Vector3 point;
    Vector3 ortho;
    Color color;

};

#endif // PLANE_H
