#ifndef SPHERE_H
#define SPHERE_H

#include "Drawable.h" // Base class: Drawable
#include "Ray.h"
#include "Vector3.h"
#include "Color.h"
#include "PhongProp.h"

class Sphere : public Drawable
{
public:
    Sphere(Vector3 center, double radius, PhongProp phong);
    virtual double intersect(Ray *r);
    virtual PhongProp getPhong();
    Vector3 getOrtho(Vector3 *point);
    Vector3 point_above(Vector3 *point);
    ~Sphere();
    
    Vector3 center;
    double radius;
    Color color;
    PhongProp phong;
};

#endif // SPHERE_H
