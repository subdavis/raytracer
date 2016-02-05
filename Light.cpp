#include "Light.h"

Light::Light(Vector3 point, Vector3 direction, Color color) : Ray(point, direction), color(color)
{
}

Light::~Light()
{
}

