#include "Color.h"
#include <cmath>

Color::Color(): r(0), g(0), b(0){
}

Color::Color(double r, double g, double b): r(r), g(g), b(b)
{
}

int Color::to_text(){
    return std::floor(r + g + b);
}

Color::~Color()
{
}

