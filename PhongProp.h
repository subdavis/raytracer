#ifndef PHONGPROP_H
#define PHONGPROP_H
#include "Vector3.h"

class PhongProp
{
public:
    PhongProp();
    PhongProp(Vector3 ka, Vector3 kd, Vector3 ks, double spower, double alpha);
    ~PhongProp();
    
    Vector3 ka;
    Vector3 ks;
    Vector3 kd;
    double spower;
    double alpha;

};

#endif // PHONGPROP_H
