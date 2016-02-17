#include <stdio.h>
#include <sstream>
#include <iostream>
#include <math.h>
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

int make_movie(){
    return 0;
}

int playground(){

    //original view. Render any n x n region
    Vector3 top_l = Vector3(-.1,.1,-.1);
    Vector3 bottom_l = Vector3(-.1,-.1,-.1);
    Vector3 top_r = Vector3(.1,.1,-.1);

    //16 x 9
    top_l = Vector3(-.166,.1,-.1);
    bottom_l = Vector3(-.166,-.1,-.1);
    top_r = Vector3(.166,.1,-.1);

    int width = 1600;
    int height = 900;
    int text_width = 32;
    int text_height = 18;

    //bits to do the fancy ascii renderer
    Color dot = Color(0,0,0,'.');  //dot in ascii, black on screen
    Color hash = Color(1,1,1,'#'); //white on screen
    Color underscore = Color(1,1,1,'_'); //white on screen

    Tracer perspective_tracer = Tracer(true, true); //lighting, d^2 lighting falloff
    Tracer text_tracer = Tracer(false, false);
    Ray cam = Ray(Vector3(0,0,0), Vector3(0,0,-1)); 
    Room perspective_room = Room(cam, top_l, top_r, bottom_l, dot);
    Renderer ppm_renderer = Renderer(width, height, 0, true, 3, 1.8); //antialiasing, sqrt(sample_size)
    Renderer text_renderer = Renderer(text_width, text_height, 0, false, 0, 1);
    
    //declare colors
    PhongProp pp1 = PhongProp(Vector3(.2,0,0), Vector3(1,0,0), Vector3(0,0,0),0);
    PhongProp pp2 = PhongProp(Vector3(0,.2,0), Vector3(0,.5,0), Vector3(.5,.5,.5), 32);
    PhongProp pp3 = PhongProp(Vector3(0,0,.2), Vector3(0,0,1), Vector3(0,0,0), 0);
    PhongProp pp4 = PhongProp(Vector3(.2,.2,.2), Vector3(1,1,1), Vector3(.1,.1,.1), 32);
    PhongProp pp5 = PhongProp(Vector3(.1,.1,.1), Vector3(1,1,1), Vector3(0,0,0), 0);
    
    //declare objects
    Sphere s1 = Sphere(Vector3(-4, 0, -7), 1, pp1, hash);
    Sphere s2 = Sphere(Vector3(0, 0, -7), 2, pp2, hash);
    Sphere s3 = Sphere(Vector3(4, 0, -7), 1, pp3, hash);
    Sphere s4 = Sphere(Vector3(0,0,4), 2, pp4, hash);
    Plane p1 = Plane(Vector3(0,-2,0), Vector3(0,1,0), pp5, underscore);
    Plane p2 = Plane(Vector3(0,0,-16), Vector3(0,0,1), pp5, dot);

    //declare lights
    Light l2 = Light(Vector3(-4, 4, -3), Color(100,100,100));
    Light l3 = Light(Vector3(4, 4, -3), Color(150,120,90));
    Light l4 = Light(Vector3(7,9,-12), Color(20, 20, 60));
    Light l5 = Light(Vector3(2,9,-12), Color(30, 60, 40));
    Light l6 = Light(Vector3(-3,9,-12), Color(80, 20, 20));
    
    // add objects to room
    perspective_room.addObject(&s1);
    perspective_room.addObject(&s2);
    perspective_room.addObject(&s3);
    perspective_room.addObject(&s4);
    perspective_room.addObject(&p1);
    perspective_room.addObject(&p2);
    perspective_room.addLight(l2);
    perspective_room.addLight(l3);
    perspective_room.addLight(l4);
    perspective_room.addLight(l5);
    perspective_room.addLight(l6);
    //create a text preview before starting the full render.
    text_tracer.trace(&perspective_room, &text_renderer);
    text_renderer.render_text();

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
    p2.reflective = true;
    p2.reflect_index = .5;
    width = 512;
    height = 512;

    perspective_tracer.trace(&perspective_room, &ppm_renderer);
    ppm_renderer.render_ppm("./Images/EXTRA.ppm");

    /*
     * Some experimental rotations  - Safe to ignore
     */

    // Vector3 plane_ortho = Vector3(0,1,0);
    // Vector3 plane_in = Vector3(0,0,-1);
    // double R = 4;
    // Vector3 center = Vector3(0,0,-7);
    // double t = -1;
    // ----- static Vector3 rotate(Vector3 point, double t, Vector3 u, Vector3 center, Vector3 n, double radius){
    // Vector3 s1_new_coords = Drawable::rotate(s1.center, t, plane_in, center, plane_ortho, R);
    // Vector3 s3_new_coords = Drawable::rotate(s3.center, t, plane_in, center, plane_ortho, R);
    // std::cout << s1_new_coords.x << s1_new_coords.y << s1_new_coords.z << std::endl;
    // std::cout << s1.center.x << s1.center.y << s1.center.z << std::endl;
    // s3.setOrigin(s3_new_coords);
    // s1.setOrigin(s1_new_coords);
    //

    // cam = Ray(Vector3(0,11,-8), Vector3(0,-1,0)); 
    // top_l = Vector3(1,10,-7);
    // bottom_l = Vector3(1,10,-9);
    // top_r = Vector3(-1,10,-7);

    // perspective_room.cam = cam;
    // perspective_room.top_l = top_l;
    // perspective_room.bottom_l = bottom_l;
    // perspective_room.top_r  = top_r;
    //Room wide_room = Room(cam, top_l, top_r, bottom_l, dot);
    // reflect_tracer.trace(&perspective_room, &reflect_renderer);
    // reflect_renderer.render_ppm("./Images/EXTRA.ppm");

    // int i = 0;
    // for (double f = 0; f < 2 * M_PI; f+= .05 * M_PI){
    //     Vector3 s1_new_coords = Drawable::rotate(s1.center, f, plane_in, center, plane_ortho, R);
    //     Vector3 s3_new_coords = Drawable::rotate(s3.center, f + M_PI, plane_in, center, plane_ortho, R);
    //     s3.setOrigin(s3_new_coords);
    //     s1.setOrigin(s1_new_coords);
    //     reflect_tracer.trace(&perspective_room, &reflect_renderer);
    //     std::ostringstream stringStream;
    //     stringStream << "./Images/movies/movie" <<  i << ".ppm" ;
    //     std::string filename = stringStream.str();

    //     reflect_renderer.render_ppm(filename.c_str());
    //     i++;
    // }
    return 0;
}

int pa1(){

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

    Tracer perspective_tracer = Tracer(false, false); //lighting, d^2 lighting falloff
    Ray cam = Ray(Vector3(0,0,0), Vector3(0,0,-1)); 
    Room perspective_room = Room(cam, top_l, top_r, bottom_l, dot);
    Renderer ppm_renderer = Renderer(width, height, 0, false, 8, 2.2); //antialiasing, sqrt(sample_size)
    Renderer text_renderer = Renderer(text_width, text_height, 0, false, 0, 1);
    
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
    Renderer alias_renderer = Renderer(width, height, 0, true, 8, 2.2);
    shadow_tracer.trace(&perspective_room, &alias_renderer);
    alias_renderer.render_ppm("./Images/PartC.ppm");
    return 0;
}

int main(int argc, char **argv)
{
    pa1();
    //playground(); // Uncomment for a really awesome render
    return 0;
}