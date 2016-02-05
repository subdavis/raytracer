#include "Renderer.h"
#include <iostream>
#include <cstdio>

Renderer::Renderer(int width, int height, int rtype): 
width(width), height(height), rtype(rtype)
{
    //Type is:
    // 0 for black and white
    // 1 for grayscale
    // 2 for color
    rowlen = width;
    pixels = new Color[width*height];
}

void Renderer::set_pixel(int x, int y, Color c){
    int dex = y * rowlen + x;
    pixels[dex] = c;
}
Color Renderer::get_pixel(int x, int y){
    int dex = y * rowlen + x;
    return pixels[dex];
}
void Renderer::render_text(){
    for (int j=0; j<height; j++){
        for(int i=0; i<width; i++){
            Color text_color = get_pixel(i, j);
            std::cout << text_color.to_text() << " ";
        }
        std::cout << std::endl;
    }
//    std::printf("done\n");
}

Renderer::~Renderer()
{
    //delete[] pixels;
}