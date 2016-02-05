#ifndef SPHERE_H
#define SPHERE_H

#include "Drawable.h" // Base class: Drawable
#include "Ray.h"
#include "Vector3.h"
#include "Color.h"

class Sphere : public Drawable
{
public:
    Sphere(Vector3 center, double radius, Color c);
    virtual double intersect(Ray *r);
    virtual Color getColor();
    Vector3 Orthogonal(Vector3 point);
    ~Sphere();
    
    Vector3 center;
    double radius;
    Color color;
};

#endif // SPHERE_H
