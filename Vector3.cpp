#include "Vector3.h"
#include <cmath>

Vector3::Vector3(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector3::Vector3(double xi, double yi, double zi){
    x = xi;
    y = yi;
    z = zi;
}

Vector3 Vector3::Scale (double scalar){
    Vector3 v (x * scalar,y * scalar,z * scalar);
    return v;
}
Vector3 Vector3::Unit(){
    Vector3 uv (x, y, z);
    return uv.Scale(1.0 / Magnitude());
}

double Vector3::Magnitude(){
    return sqrt( x*x + y*y + z*z);
}

Vector3 Vector3::add_const(double c){
    Vector3 v (x+c, y+c, z+c);
    return v;
}
Vector3 Vector3::add(Vector3 b){
    Vector3 v (x+b.x, y+b.y, z+b.z);
    return v;
}
Vector3 Vector3::multiply(Vector3 b){
    Vector3 v (x*b.x, y*b.y, z*b.z);
    return v;
}

double Vector3::dot(Vector3 b){
    return (x*b.x + y*b.y + z*b.z);
}
Vector3 Vector3::cross(Vector3 b){
    //unimplemented
}

Vector3 Vector3::minus(Vector3 b){
    Vector3 v (x - b.x, y - b.y, z - b.z);
    return v;
}

Vector3::~Vector3(){}
