#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Ray.h"
#include "Color.h"
#include "PhongProp.h"

class Drawable
{
public:
    virtual double intersect(Ray *r) = 0;
    virtual PhongProp getPhong() = 0;
    virtual Vector3 getOrtho(Vector3 *point) = 0;
    virtual Vector3 point_above(Vector3 *point) = 0;
    virtual double get_reflect() = 0;
    virtual bool is_reflective() = 0;
    virtual ~Drawable() {}
//    Drawable();
//    Drawable* parent;
//    void addParent(Drawable* parent) {this->parent = parent;}
};

#endif // DRAWABLE_H
