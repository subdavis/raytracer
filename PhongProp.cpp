#include "PhongProp.h"
PhongProp::PhongProp(){}

PhongProp::PhongProp(Vector3 ka, Vector3 kd, Vector3 ks, double spower, double alpha):
ka(ka), kd(kd), ks(ks), spower(spower), alpha(alpha)
{
}

PhongProp::~PhongProp()
{
}

