#include "Sphere.h"
#include <cmath>

Sphere::Sphere(Vector3 center, double radius, Color c):
center(center), radius(radius), color(c)
{
}

double Sphere::intersect(Ray *r){
    //returns distance to the closest intersection
    Vector3 d = r->d;
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
        double d2 = (b - sqrt(inner_root)) / ddd;
        //perform for the shortest distance
        if (d1 < d2){
            return d1;
        } else {
            return d2;
        }
    }
}

Vector3 Sphere::Orthogonal(Vector3 point){
    //returns an orthogonal unit vector
}

Sphere::~Sphere()
{
}

