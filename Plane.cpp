#include "Plane.h"

Plane::Plane(Vector3 point, Vector3 ortho, Color c): 
point(point), ortho(ortho), color(c)
{
}

double Plane::intersect(Ray *r){
//    top = np.dot( (ray.point - self.point) , self.d )
//        bottom = np.dot(ray.d, self.d)
//        if bottom == 0:
//            return (-1, None, False, None)       
//        else:
//            t = (-1 * top) / bottom
//            if t > 0:       
//                P = ray.point + t*(ray.d)
//                return (t, P, True, self.d)
//            else:
//                return (-1, None, False, None)
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

Color Plane::getColor(){
    return color;
}

Plane::~Plane()
{
}

