#include "Tracer.h"
#include <iostream>
#include "Drawable.h"

Tracer::Tracer(bool antialias, bool lighting, bool shadows): 
antialias(antialias), lighting(lighting), shadows(shadows){}

void Tracer::trace(Room *room, Renderer *r){
    
    //generate the 2d array of pixel points that the tracer will shine rays through.
    //The room pre-generated this for us.
    Ray *rays = room->find_pixel_points(r->width, r->height);
    
    Ray ray;
    double shortest = -1.0;
    double compare;
    int dex;
    int tocheck = room->objs.size();
    Drawable *obj;
    Vector3 iortho;
    Vector3 ipoint;
    int shortest_index;
    
    for(int j=0; j<r->height; j++){
        for(int i=0; i<r->width; i++){
            dex = j * r->width + i;
            ray = rays[dex];
            
            //iterate over the items in the scene and get the closest intersection.
            shortest = -1.0;
            for(int o=0;o<tocheck;o++){
                obj = room->objs[o];
                compare = obj->intersect(&ray);
                if (compare != -1.0){
                    if (compare < shortest || shortest == -1.0){
                        shortest = compare;
                        //ipoint = room->cam.point.add( ray.d.Scale(shortest) );
                        //iortho = obj->get_ortho(&ipoint)
                        //icolor = obj->getColor();
                        shortest_index = o;
                    }
                }
            }
            //we didn't find an intersection
            if (shortest == -1.0){
                r->set_pixel(i,j, room->bg);
            } else {
                //do lighting using the intersect point and ortho
                r->set_pixel(i, j, room->objs[shortest_index]->getColor());
            }
        }
    }
}

Tracer::~Tracer(){}

