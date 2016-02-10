#ifndef RENDERER_H
#define RENDERER_H
#include "Color.h"

class Renderer
{
public:
    Renderer(int width, int height, int rtype, bool antialias, int sample_index);
    ~Renderer();
    void set_pixel(int x, int y, Color c);
    Color get_pixel(int x, int y);
    void render_text();
    void render_ppm(const char *filename);
    int getWidth();
    int getHeight();
    int width;
    int height;
    bool antialias;
    int sample_index;

private:
    int rtype;
    int rowlen;
    double top;
    Color *pixels;
};

#endif // RENDERER_H
