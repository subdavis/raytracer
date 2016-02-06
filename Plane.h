#ifndef PLANE_H
#define PLANE_H

#include "Drawable.h" // Base class: Drawable
#include "Vector3.h"
#include "Color.h"
#include "PhongProp.h"

class Plane : public Drawable
{
public:
    Plane() {}
    Plane(Vector3 point, Vector3 ortho, PhongProp phong);
    virtual PhongProp getPhong();
    Vector3 getOrtho(Vector3 *point);
    Vector3 point_above(Vector3 *point);
    virtual double intersect(Ray *r);
    virtual double get_reflect();
    virtual bool is_reflective();
    ~Plane();
    Vector3 point;
    Vector3 ortho;
    PhongProp phong;
    bool reflective;
    double reflect_index;

};

#endif // PLANE_H
