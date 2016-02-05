#include "PhongProp.h"
PhongProp::PhongProp(){}

PhongProp::PhongProp(Vector3 ka, Vector3 kd, Vector3 ks, double spower):
ka(ka), kd(kd), ks(ks), spower(spower)
{
}

PhongProp::~PhongProp()
{
}

