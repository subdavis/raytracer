#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color();
    Color(double r, double g, double b);
    int to_text();
    ~Color();
    double r;
    double g;
    double b;

};

#endif // COLOR_H
