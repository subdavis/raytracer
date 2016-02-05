#include "Plane.h"

Plane::Plane(Vector3 point, Vector3 ortho, Color c): 
point(point), ortho(ortho), color(c)
{
}

double Plane::intersect(Ray *r){
    return 0.0;
}

Plane::~Plane()
{
}

