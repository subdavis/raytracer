#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "Ray.h"
#include "Color.h"

class Drawable
{
public:
    virtual double intersect(Ray *r) = 0;
    virtual ~Drawable() {}
//    Drawable();
//    Drawable* parent;
//    void addParent(Drawable* parent) {this->parent = parent;}
    Color *color;
};

#endif // DRAWABLE_H
