#include "Tracer.h"
#include <iostream>
#include <cmath>
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
    //refactor colors into vectors
    Vector3 I = Vector3(0,0,0);
    Vector3 Ia;
    Vector3 Id;
    Vector3 Is;
    
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
                I = Ia = Id = Is = Vector3(0,0,0);
                for (int li=0; li<lights_tocheck;li++){
                    
                    light = room->lights[li];
                    Vector3 to_light = light.point.minus(ipoint).Unit();
                    Vector3 reflect = iortho.Unit().Scale(2 * (iortho.Unit().dot(to_light))).minus(to_light).Unit();
                    Vector3 to_eye = ray.d.Scale(-1);
                    //ambient
                    Ia = Ia.add(Vector3(iphong.ka.x * light.color.r , iphong.ka.y * light.color.g, iphong.ka.z * light.color.b));
                    //diffuse
                    double dot = iortho.Unit().dot(to_light);
                    if (dot >= 0){
                        Id = Id.add(Vector3(iphong.kd.x * dot * light.color.r , iphong.kd.y * dot * light.color.g , iphong.kd.z * dot * light.color.b));
                    } else {
                        Id = Id.add(Vector3(0,0,0));
                    }
                    //specular
                    double sr = iphong.ks.x * pow( (reflect.dot(to_eye)), iphong.spower) * light.color.r;
                    double sg = iphong.ks.y * pow( (reflect.dot(to_eye)), iphong.spower) * light.color.g;
                    double sb = iphong.ks.z * pow( (reflect.dot(to_eye)), iphong.spower) * light.color.b;
                    Is = Is.add(Vector3(sr, sg, sb));
                    //combine all the lights
                    I = I.add(Id).add(Ia).add(Is);
                }
                r->set_pixel(i, j, Color(I.x,I.y,I.z));
            }
        }
    }
}

Tracer::~Tracer(){}

