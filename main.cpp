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
#include "PhongProp.h"

int main(int argc, char **argv)
{
    /*
     * Part 1 Render
     */
 
    //original view. Render any n x n region
    Vector3 top_l = Vector3(-.1,.1,-.1);
    Vector3 bottom_l = Vector3(-.1,-.1,-.1);
    Vector3 top_r = Vector3(.1,.1,-.1);

    int width = 512;
    int height = 512;
    int text_width = 20;
    int text_height = 20;

    //bits to do the fancy ascii renderer
    Color dot = Color(0,0,0,'.');  //dot in ascii, black on screen
    Color hash = Color(1,1,1,'#'); //white on screen
    Color underscore = Color(1,1,1,'_'); //white on screen

    Tracer perspective_tracer = Tracer(false, true); //lighting, d^2 lighting falloff
    Ray cam = Ray(Vector3(0,0,0), Vector3(0,0,-1)); 
    Room perspective_room = Room(cam, top_l, top_r, bottom_l, dot);
    Renderer ppm_renderer = Renderer(width, height, 0, false, 8); //antialiasing, sqrt(sample_size)
    Renderer text_renderer = Renderer(text_width, text_height, 0, false, 0);
    
    //declare colors
    PhongProp pp1 = PhongProp(Vector3(.2,0,0), Vector3(1,0,0), Vector3(0,0,0),0);
    PhongProp pp2 = PhongProp(Vector3(0,.2,0), Vector3(0,.5,0), Vector3(.5,.5,.5), 32);
    PhongProp pp3 = PhongProp(Vector3(0,0,.2), Vector3(0,0,1), Vector3(0,0,0), 0);
    PhongProp pp4 = PhongProp(Vector3(.2,.2,.2), Vector3(1,1,1), Vector3(0,0,0), 0);
    
    //declare objects
    Sphere s1 = Sphere(Vector3(-4, 0, -7), 1, pp1, hash);
    Sphere s2 = Sphere(Vector3(0, 0, -7), 2, pp2, hash);
    Sphere s3 = Sphere(Vector3(4, 0, -7), 1, pp3, hash);
    Plane p1 = Plane(Vector3(0,-2,0), Vector3(0,1,0), pp4, underscore);

    //declare lights
    Light l1 = Light(Vector3(-4, 4, -3), Color(1,1,1));
    
    //add objects to room
    perspective_room.addObject(&s1);
    perspective_room.addObject(&s2);
    perspective_room.addObject(&s3);
    perspective_room.addObject(&p1);
    perspective_room.addLight(l1);
    
    perspective_tracer.trace(&perspective_room, &ppm_renderer);
    perspective_tracer.trace(&perspective_room, &text_renderer);
    
    //create a text preview before starting the full render.
    text_renderer.render_text();
    //assumes that executable is run within the ./Build directory
    ppm_renderer.render_ppm("./Images/PartA.ppm");
    
    /*
     * Part 2 - shading and shadows
     */
    Tracer shadow_tracer = Tracer(true, false);
    shadow_tracer.trace(&perspective_room, &ppm_renderer);
    ppm_renderer.render_ppm("./Images/PartB.ppm");
    
    /*
     * Part 3 - With Antialiasing
     */
    Renderer alias_renderer = Renderer(width, height, 0, true, 8);
    shadow_tracer.trace(&perspective_room, &alias_renderer);
    alias_renderer.render_ppm("./Images/PartC.ppm");

    /*
     * EXTRA - With Reflection and lighting falloff.
     */

    s1.reflective = true;
    s1.reflect_index = .6;
    s2.reflective = true;
    s2.reflect_index = .8;
    s3.reflective = true;
    s3.reflect_index = .6;
    p1.reflective = true;
    p1.reflect_index = .2;

    width = 1000;
    height = 1000;

    Light l2 = Light(Vector3(-4, 4, -3), Color(100,100,100));
    Light l3 = Light(Vector3(4, 4, -3), Color(100,100,100));
    perspective_room.addLight(l2);
    perspective_room.addLight(l3);

    Tracer reflect_tracer = Tracer(true, true);
    Renderer reflect_renderer = Renderer(width, height, 0, false, 3);
    reflect_tracer.trace(&perspective_room, &reflect_renderer);
    reflect_renderer.render_ppm("./Images/EXTRA.ppm");
    
    return 0;
}
