#ifndef COLOR_H
#define COLOR_H
#include <string>

class Color
{
public:
    Color();
    Color(double r, double g, double b);
    Color(double r, double g, double b, char char_rep);
    char to_text();
    std::string to_ppm(double max);
    std::string to_ppm(double oldmax, double newmax, double gamma);
    // ~Color();
    double r;
    double g;
    double b;
    char char_rep;
    std::string static ntos(int i);

};

#endif // COLOR_H
