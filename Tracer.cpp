#include "Tracer.h"
#include <iostream>
#include "Drawable.h"
#include "Light.h"

Tracer::Tracer(bool antialias, bool lighting, bool shadows): 
antialias(antialias), lighting(lighting), shadows(shadows){}

void Tracer::trace(Room *room, Renderer *r){
    
    //generate the 2d array of pixel points that the tracer will shine rays through.
    //The room pre-generated this for us.
    Ray *rays = room->find_pixel_points(r->width, r->height);
    
    //variables for the ray array iterator
    Ray ray;
    double shortest;
    double compare;
    int dex;
    //data for objects and lights in the room
    int objs_tocheck = room->objs.size();
    int lights_tocheck = room->lights.size();
    Drawable *obj;
    Light light;
    //data for a given intersection point
    Vector3 iortho;
    Vector3 ipoint;
    PhongProp iphong;
    int shortest_index;
    //for light stuff
    double ir=.5;
    double ig=.5;
    double ib=.5;
    //ambient
    double Iar;
    double Iag;
    double Iab;
    //diffuse
    double Idr;
    double Idg;
    double Idb;
    
    for(int j=0; j<r->height; j++){ // y
        for(int i=0; i<r->width; i++){ // x
            dex = j * r->width + i;
            ray = rays[dex];
            
            //iterate over the items in the scene and get the closest intersection.
            shortest = -1.0;
            for(int o=0; o<objs_tocheck; o++){
                obj = room->objs[o];
                compare = obj->intersect(&ray);
                if (compare != -1.0){
                    if (compare < shortest || shortest == -1.0){
                        shortest = compare;
                        shortest_index = o;
                    }
                }
            }
            //we didn't find an intersection
            if (shortest == -1.0){
                r->set_pixel(i,j, room->bg);
            } else {
                //do lighting using the intersect point and ortho
                ipoint = room->cam.point.add( ray.d.Scale(shortest) );
                iortho = room->objs[shortest_index]->getOrtho(&ipoint);
                iphong = room->objs[shortest_index]->getPhong();
                //iterate over the lights to get illumiation at the point
                ir=0;
                ig=0;
                ib=0;
                Iar = 0;
                Iag = 0;
                Iab = 0;
                Idr = 0;
                Idg = 0;
                Idb = 0;
                for (int li=0; li<lights_tocheck;li++){
                    light = room->lights[li];
                    //ambient
                    Iar += iphong.ka.x * light.color.r;
                    Iag += iphong.ka.y * light.color.g;
                    Iab += iphong.ka.z * light.color.b;
                    //diffuse
                    double dot = iortho.Unit().dot(light.point.minus(ipoint).Unit());
                    if (dot >= 0){
                        Idr += iphong.kd.x * dot * light.color.r;
                        Idg += iphong.kd.y * dot * light.color.g;
                        Idb += iphong.kd.z * dot * light.color.b;
                    } else {
                        Idr, Idg, Idb = 0;
                    }
                     
                    //combine all the lights
                    ir += Iar + Idr;
                    ig += Iag + Idg;
                    ib += Iab + Idb;
                }
                r->set_pixel(i, j, Color(ir,ig,ib));
            }
        }
    }
}

Tracer::~Tracer(){}

