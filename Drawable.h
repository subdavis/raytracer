#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Ray.h"
#include "Color.h"
#include "PhongProp.h"
#include "Vector3.h"
#include <math.h>

class Drawable
{
public:
    virtual double intersect(Ray *r) = 0;
    virtual PhongProp getPhong() = 0;
    virtual Vector3 getOrtho(Vector3 *point) = 0;
    virtual Vector3 point_above(Vector3 *point) = 0;
    virtual double get_reflect() = 0;
    virtual Color getColor() = 0;
    virtual bool is_reflective() = 0;
    virtual ~Drawable() {}
    static Vector3 rotate(Vector3 point, double t, Vector3 u, Vector3 center, Vector3 n, double radius){
        //code for doing rotation
        //P = R cos ( t ) * u + R sin ( t ) * n ×  u + c
        Vector3 P = u.Scale(radius * cos(t)).add(n.cross(u).Scale(radius * sin(t)) ).add(center);
        return P;
    }
//    Drawable();
//    Drawable* parent;
//    void addParent(Drawable* parent) {this->parent = parent;}

};

#endif // DRAWABLE_H
