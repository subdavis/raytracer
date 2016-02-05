#ifndef VECTOR3_H
#define VECTOR3_H
class Vector3
{
    public:
        double x;
        double y;
        double z;
    
        Vector3();
        Vector3(double x, double y, double z);
        ~Vector3();
        Vector3 Scale (double scalar);
        double dot(Vector3 b);
        Vector3 Unit();
        Vector3 minus(Vector3 b);
        Vector3 add_const(double c);
        Vector3 add(Vector3 b);
        Vector3 multiply(Vector3 b);
        Vector3 cross(Vector3 b);
        double Magnitude();
    
    private:

};

#endif // VECTOR3_H
