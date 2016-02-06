#include "Tracer.h"
#include <iostream>
#include <cmath>
#include "Drawable.h"
#include "Light.h"

Tracer::Tracer(bool antialias, bool lighting): 
antialias(antialias), lighting(lighting){
    depth = 0;
    falloff = false;
}

void Tracer::trace(Room *room, Renderer *r){
    //generate the 2d array of pixel points that the tracer will shine rays through.
    //The room pre-generated this for us.
    Ray *rays = room->find_pixel_points(r->width, r->height);
    
    //data for objects and lights in the room
    objs_tocheck = room->objs.size();
    lights_tocheck = room->lights.size();
    int dex;
    
    for(int j=0; j<r->height; j++){ // y
        for(int i=0; i<r->width; i++){ // x
            dex = j * r->width + i;
            depth = 0;
            r->set_pixel(i,j, recursive_trace(rays[dex], room, r) );
        }
    }
}

Color Tracer::recursive_trace(Ray start_ray, Room *room, Renderer *r){
    /*
     * Declare the variables that will be set and reset during calls to this function
     */
    //data for objects and lights in the room
    Drawable *iobj;
    Light ilight;
    //data for a given intersection point
    Vector3 iortho;
    Vector3 ipoint;
    PhongProp iphong;
    double shortest;
    double compare;
    int shortest_index;
    //for light stuff
    bool direct_path;
    Vector3 I;
    Vector3 Ia = Vector3(0,0,0);
    Vector3 Id = Vector3(0,0,0);
    Vector3 Is = Vector3(0,0,0);
    //iterate over the items in the scene and get the closest intersection.
    shortest = -1;
    for(int o=0; o<objs_tocheck; o++){
        iobj = room->objs[o];
        compare = iobj->intersect(&start_ray);
        if (compare != -1){
            if (compare < shortest || shortest == -1){
                shortest = compare;
                shortest_index = o;
            }
        }
    }
    if (shortest == -1){
        //we didn't find an intersection
        return room->bg;
    } else {
        //do lighting using the intersect point and ortho
        ipoint = start_ray.point.add( start_ray.d.Scale(shortest) );
        iortho = room->objs[shortest_index]->getOrtho(&ipoint);
        iphong = room->objs[shortest_index]->getPhong();
        
        //iterate over the lights to get illumiation at the point
        I = Ia = Id = Is = Vector3(0,0,0);
        for (int li=0; li<lights_tocheck;li++){
            ilight = room->lights[li];
            Vector3 to_light = ilight.point.minus(ipoint).Unit();
            double distance_to_light = ilight.point.minus(ipoint).Magnitude();
            double falloff_scalar = 1;
            if (falloff){
                falloff_scalar = 1/ pow(distance_to_light, 2);
            }
            Vector3 reflect = iortho.Unit().Scale(2 * (iortho.Unit().dot(to_light))).minus(to_light).Unit();
            Vector3 to_eye = start_ray.d.Scale(-1);
            //ambient - don't put this under the floor.  That's bad.
            Ia = Ia.add(Vector3(iphong.ka.x * ilight.color.r , iphong.ka.y * ilight.color.g, iphong.ka.z * ilight.color.b));
            //Only run the rest of the lighting algo if there's a direct path to one of the lights
            direct_path = true;
            //Check the others
            for(int o=0; o< objs_tocheck; o++){
                iobj = room->objs[o];
                //make a unit ray from the intersect point, using a point just above the surface
//TODO---->     Bug here - this should be the direct vector to the light
                Ray r_to_light = Ray(ipoint.add(iortho.Scale(.01)), to_light);
                compare = iobj->intersect(&r_to_light);
//TODO---->     Make sure the intersect doesn't happen behind the light.  for now, we can assume that it wont.
                if (compare == -1){
                    //there is a direct path to the current light.
                } else {
                    //something was in the way.  Don't do anything else right now.
                    direct_path = false;
                }
            }
            // do this after we check all the objects
            if (direct_path){
                //diffuse
                double dot = iortho.Unit().dot(to_light) * falloff_scalar;
                if (dot >= 0){
                    Id = Id.add(Vector3(iphong.kd.x * dot * ilight.color.r , iphong.kd.y * dot * ilight.color.g , iphong.kd.z * dot * ilight.color.b));
                } else {
                    Id = Id.add(Vector3(0,0,0));
                }
                //specular
                //only do specular if this is the first recursion
//TODO:--->     analyze this
//                if (depth == 0){
                    double sr = iphong.ks.x * pow( (reflect.dot(to_eye)), iphong.spower) * ilight.color.r * falloff_scalar;
                    double sg = iphong.ks.y * pow( (reflect.dot(to_eye)), iphong.spower) * ilight.color.g * falloff_scalar;
                    double sb = iphong.ks.z * pow( (reflect.dot(to_eye)), iphong.spower) * ilight.color.b * falloff_scalar;
                    Is = Is.add(Vector3(sr, sg, sb));
//                }
            }
            //combine all the lights
            I = I.add(Id).add(Ia).add(Is);
            //try some reflection
            if (room->objs[shortest_index]->is_reflective() && depth < 5){
                depth++;
                //get the reflect vector
                //c1 = -dot_product( N, V )
                //Rl = V + (2 * N * c1 )
                double c1 = -1 * iortho.dot(start_ray.d);
                Vector3 ref_u = start_ray.d.add(iortho.Scale(2*c1)).Unit();
                Ray ref_r = Ray(ipoint, ref_u);
                Color result = recursive_trace(ref_r, room, r);
                I = I.add( Vector3(result.r, result.g, result.b).Scale( room->objs[shortest_index]->get_reflect() ));
            }
        }
        return Color(I.x,I.y,I.z);
    }
}

Tracer::~Tracer(){}

