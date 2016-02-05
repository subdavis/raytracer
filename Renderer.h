#ifndef RENDERER_H
#define RENDERER_H
#include "Color.h"

class Renderer
{
public:
    Renderer(int width, int height, int rtype);
    ~Renderer();
    void set_pixel(int x, int y, Color c);
    Color get_pixel(int x, int y);
    void render_text();
    void render_ppm();
    int width;
    int height;
private:
    int rtype;
    int rowlen;
    double top;
    Color *pixels;
};

#endif // RENDERER_H
