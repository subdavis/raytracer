#include <stdio.h>
#include <sstream>
#include <iostream>
#include "Drawable.h"
#include "Color.h"
#include "Light.h"
#include "Plane.h"
#include "Ray.h"
#include "Room.h"
#include "Sphere.h"
#include "Vector3.h"
#include "Renderer.h"
#include "Tracer.h"

int unit_tests(){
    
    printf("Try Creating independent objects\n");
    Color c = Color(0, .5, .5);
    Light l = Light(Vector3(0,0,0), Vector3(0,-1,0), c);
    Plane p = Plane(Vector3(0,0,0), Vector3(0,1,0), c);
    Ray r = Ray(Vector3(0,0,-20), Vector3(0,0,1));
    Sphere s = Sphere(Vector3(0,0,0), 2, c);
    
    printf("Intersection at %.4f\n",s.intersect(&r));
    std::cout << c.ntos(255);
    
    printf("Test some vector math\n");
    Vector3 a = Vector3(9, 5, -9);
    Vector3 b = Vector3(1,0,5);
    bool check = -36.0 == a.dot(b);
    printf("%d\n", check);
    
    printf("Render a blank sample to the console.\n");
    int w = 10;
    int h = 10;
    Renderer test_rndr = Renderer(w, h, 0);
    Color tc = Color(1, 1, 0);
    for(int j = 0; j<h;j++){
        for (int i=0;i<w;i++){
            test_rndr.set_pixel(i,j,tc);
        }
    }
    test_rndr.render_text();
    return 0;
}

int main(int argc, char **argv)
{
    //unit_tests();
    
    Ray cam = Ray(Vector3(0,0,0), Vector3(0,0,-1));
    Vector3 top_l = Vector3(.1,-.1,-.1);
    Vector3 top_r = Vector3(-.1,-.1,-.1);
    Vector3 bottom_l = Vector3(.1,.1,-.1);
    
    printf("Now Try Rendering a real room\n");
    int width = 1000;
    int height = 1000;
    int tw = 30;
    int th = 30;
    Tracer perspective_tracer = Tracer(false, false, false);
    Room perspective_room = Room(cam, top_l, top_r, bottom_l, Color(0,0,0));
    //Renderer text_renderer = Renderer(tw, th, 0);
    Renderer ppm_renderer = Renderer(width, height, 0);
    
    Color c1 = Color(.5,0,0);
    Color c2 = Color(0,.5,0);
    Color c3 = Color(0,0,.5);
    Color c4 = Color(.4,.4,.4);
    Sphere s1 = Sphere(Vector3(-4, 0, -7), 1, c1);
    Sphere s2 = Sphere(Vector3(0, 0, -7), 2, c2);
    Sphere s3 = Sphere(Vector3(4, 0, -7), 1, c3);
    Plane p1 = Plane(Vector3(0,2,0), Vector3(0,1,0), c4);
    
    perspective_room.addObject(&s1);
    perspective_room.addObject(&s2);
    perspective_room.addObject(&s3);
    perspective_room.addObject(&p1);
    
    //perspective_tracer.trace(&perspective_room, &text_renderer);
    perspective_tracer.trace(&perspective_room, &ppm_renderer);
    
    //text_renderer.render_text();
    ppm_renderer.render_ppm();
    return 0;
}
