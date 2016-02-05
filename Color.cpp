#include "Color.h"
#include <cmath>
#include <sstream>
#include <iostream>

Color::Color(): r(0), g(0), b(0){
}

Color::Color(double r, double g, double b): r(r), g(g), b(b)
{
}

int Color::to_text(){
    return std::floor(r + g + b);
}

std::string Color::to_ppm(int max){
    std::string ri = ntos(round(r * max));
    std::string gi = ntos(round(g * max));
    std::string bi = ntos(round(b * max));
    return ri + " " + gi + " " + bi;
    
}

std::string Color::ntos(int i){
    std::ostringstream convert;
    convert << i;
    std::string out = convert.str();
    return out;
}

Color::~Color()
{
}

