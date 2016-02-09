#include "Plane.h"

Plane::Plane(Vector3 point, Vector3 ortho, PhongProp phong): 
point(point), ortho(ortho), phong(phong)
{
    reflect_index = 0;
    reflective = false;
}

Plane::Plane(Vector3 point, Vector3 ortho, PhongProp phong, Color c): 
point(point), ortho(ortho), phong(phong), color(c)
{
    reflect_index = 0;
    reflective = false;
}

double Plane::intersect(Ray *r){
    double top = r->point.minus(point).dot(ortho);
    double bottom = r->d.dot(ortho);
    if (bottom == 0){
        return -1;
    } else {
        double t = (top * -1) / bottom;
        if (t > 0){
            return t;
        } else {
            return -1;
        }
    }
}

PhongProp Plane::getPhong(){
    return phong;
}

Color Plane::getColor(){
    return color;
}

Vector3 Plane::getOrtho(Vector3 *point){
    return ortho;
}
Vector3 Plane::point_above(Vector3 *point){
    return point->add(ortho.Scale(.01));
}
bool Plane::is_reflective(){
    return reflective;
}
double Plane::get_reflect(){
    return reflect_index;
}

Plane::~Plane()
{
}

