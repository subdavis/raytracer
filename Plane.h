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
    Plane(Vector3 point, Vector3 ortho, PhongProp phong, Color c);
    virtual PhongProp getPhong();
    virtual Color getColor();
    Vector3 getOrtho(Vector3 *point);
    Vector3 point_above(Vector3 *point);
    virtual double intersect(Ray *r);
    virtual double get_reflect();
    virtual bool is_reflective();
    ~Plane();
    Vector3 point;
    Vector3 ortho;
    Color color;
    PhongProp phong;
    bool reflective;
    double reflect_index;

};

#endif // PLANE_H
