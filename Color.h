#ifndef COLOR_H
#define COLOR_H
#include <string>

class Color
{
public:
    Color();
    Color(double r, double g, double b);
    int to_text();
    std::string to_ppm(int max);
    ~Color();
    double r;
    double g;
    double b;
    std::string static ntos(int i);

};

#endif // COLOR_H
