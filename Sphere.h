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
    Sphere(Vector3 center, double radius, PhongProp phong, Color c);
    virtual double intersect(Ray *r);
    virtual PhongProp getPhong();
    Vector3 getOrtho(Vector3 *point);
    Vector3 point_above(Vector3 *point);
    void setOrigin(Vector3 neworigin);
    bool is_reflective();
    double get_reflect();
    virtual Color getColor();
    ~Sphere();
    
    Vector3 center;
    double radius;
    Color color;
    PhongProp phong;
    bool reflective;
    double reflect_index;
};

#endif // SPHERE_H
