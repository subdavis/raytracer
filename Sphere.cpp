#include "Sphere.h"
#include <cmath>

Sphere::Sphere(Vector3 center, double radius, PhongProp phong):
center(center), radius(radius), phong(phong)
{
    reflect_index = 0;
    reflective = false;
}

double Sphere::intersect(Ray *r){
    //returns distance to the closest intersection
    Vector3 d = r->d; //direction
    Vector3 e = r->point;
    Vector3 c = center;
    double R = radius;
    Vector3 emc = e.minus(c);
    double ddd = d.dot(d);
    double b = d.Scale(-1).dot(emc);
    double inner_root = pow(d.dot(emc),2) - (ddd * ( emc.dot(emc) - pow(R, 2)));
    if (inner_root < 0){
        //an intersection was not found
        return -1.0;
    }else{
        double d1 = (b + sqrt(inner_root)) / ddd;
        double d2 = (b - sqrt(inner_root)) / ddd; //should be shortest
        //perform for the shortest distance
        if (d2 < d1 && d2 >= 0){
            return d2;
        } else if (d1 >= 0) {
            return d1;
        } else {
            return -1.0;
        }
    }
}

Vector3 Sphere::getOrtho(Vector3 *point){
    //returns an orthogonal unit vector
    return point->minus(center).Unit();
}

PhongProp Sphere::getPhong(){
    return phong;
}

Vector3 Sphere::point_above(Vector3 *point){
    Vector3 ortho = getOrtho(point).Scale(radius * 1.01);
    return center.add(ortho);
}
bool Sphere::is_reflective(){
    return reflective;
}
double Sphere::get_reflect(){
    return reflect_index;
}

Sphere::~Sphere()
{
}