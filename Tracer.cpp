#include "Tracer.h"
#include <iostream>
#include <cmath>
#include "Drawable.h"
#include "Light.h"

Tracer::Tracer(bool lighting, bool falloff): 
lighting(lighting), falloff(falloff){
    depth = 0;
    max_depth = 5;
}

void Tracer::trace(Room *room, Renderer *renderer){
    int width = renderer->getWidth();
    int height = renderer->getHeight();
    //generate the 2d array of rays through the camera and each pixel
    Ray *rays = room->find_pixel_points(renderer);
    //data for objects and lights in the room
    num_objects = room->objs.size();
    num_lights = room->lights.size();
    int dex;
    for(int j=0; j< height ; j++){ // y
        for(int i=0; i< width ; i++){ // x
            dex = j * width + i;
            depth = 0;
            renderer->set_pixel(i,j, recursive_trace(rays[dex], room, renderer) );
        }
    }
}

Color Tracer::recursive_trace(Ray start_ray, Room *room, Renderer *r){

    /*
     * Recursive Tracer Function
     * Invoked for every pixel in the render
     * Called recursively for reflective objects to a max depth declared in the constructor
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
    bool inside_sphere;
    Vector3 I;
    Vector3 Ia; //ambient
    Vector3 Id; //diffuse
    Vector3 Is; //specular
    //iterate over the items in the scene and get the closest intersection.
    shortest = -1;
    for(int o=0; o<num_objects; o++){
        iobj = room->objs[o];
        compare = iobj->intersect(&start_ray);
        if (compare != -1){
            if (compare < shortest || shortest == -1){
                shortest = compare;
                shortest_index = o;}}
    }
    
    if (shortest == -1){
        
        //we didn't find an intersection
        return room->bg;
    
    } else if (lighting) {
        //there was an intersection and lighting is configured on

        //do lighting using the intersect point and ortho
        ipoint = start_ray.point.add( start_ray.d.Scale(shortest) );
        iortho = room->objs[shortest_index]->getOrtho(&ipoint);
        iphong = room->objs[shortest_index]->getPhong();
        
        inside_sphere = false;
        
        //iterate over the lights to get illumiation at the point
        for (int li=0; li<num_lights;li++){
            
            ilight = room->lights[li];
            Vector3 vector_to_light = ilight.point.minus(ipoint).Unit();
            double distance_to_light = ilight.point.minus(ipoint).Magnitude();
            double falloff_scalar = falloff ? 1/pow(distance_to_light, 2) : 1;
            Vector3 reflect = iortho.Unit().Scale(2 * (iortho.Unit().dot(vector_to_light))).minus(vector_to_light).Unit();
            Vector3 to_eye = start_ray.d.Scale(-1);
            
            /*
             * Ambient Lighting
             */
            Ia = Ia.add(Vector3(iphong.ka.x * ilight.color.r , iphong.ka.y * ilight.color.g, iphong.ka.z * ilight.color.b));
            Ia = Ia.Scale(falloff_scalar);
            
            //Only run the rest of the lighting algo if there's a direct path to one of the lights
            direct_path = true;
            
            //make a unit ray from the intersect point, using a point just above the surface
            Ray r_to_light = Ray(ipoint.add(iortho.Scale(.001)), vector_to_light);
            
            //Check every other onbject in the room for light blocking
            for(int o=0; o< num_objects; o++){
                iobj = room->objs[o];
                compare = iobj->intersect(&r_to_light);

                if (compare == -1){
                    //there is a direct path to the current light.
                } else {

                    //check if the collission is behind the light or in front of it.
                    if (compare > (distance_to_light + .1)){
                        //it happened behind the light.  All is well

                    } else {
                        //something was in the way.  Don't do anything else right now.
                        direct_path = false;
                    }
                    
                    if (compare < 0){
                        //a negative distance will be returned if the shortest point of interseciton is behind the search ray
                        inside_sphere = true;
                    }
                }
            }
            
            // do this after we check all the objects
            if (direct_path ){
                
                /*
                 * Diffuse Lighting
                 */
                double dot = iortho.dot(vector_to_light.Scale(falloff_scalar));
                if (dot >= 0){
                    Id = Id.add(Vector3(iphong.kd.x * dot * ilight.color.r , iphong.kd.y * dot * ilight.color.g , iphong.kd.z * dot * ilight.color.b));
                } else {
                    Id = Id.add(Vector3(0,0,0));
                }
                
                /*
                 * Specular Lighting
                 */
                double sr = iphong.ks.x * pow( (reflect.dot(to_eye)), iphong.spower) * ilight.color.r;
                double sg = iphong.ks.y * pow( (reflect.dot(to_eye)), iphong.spower) * ilight.color.g;
                double sb = iphong.ks.z * pow( (reflect.dot(to_eye)), iphong.spower) * ilight.color.b;
                Is = Is.add(Vector3(sr, sg, sb));
                Is = Is.Scale(falloff_scalar);
            }
            //combine all the effects.  Done for every light.
            I = I.add(Id).add(Ia).add(Is);
        }
        
        /*
         * Reflection!
         */
        if (room->objs[shortest_index]->is_reflective() && depth < max_depth && !inside_sphere){
            depth++;
            //get the reflect vector
            //c1 = -dot_product( N, V )
            //Rl = V + (2 * N * c1 )
            double c1 = -1 * iortho.dot(start_ray.d);
            Vector3 ref_u = start_ray.d.add(iortho.Scale(2*c1)).Unit();
            //move the origin away from the object.
            Ray ref_r = Ray(ipoint.add(ref_u.Scale(.0001)), ref_u);
            Color result = recursive_trace(ref_r, room, r);
            I = I.add( Vector3(result.r, result.g, result.b).Scale( room->objs[shortest_index]->get_reflect() ));
        }
        return Color(I.x,I.y,I.z);
    } else {
        //lighting was off.
        return room->objs[shortest_index]->getColor();
    }
}

Tracer::~Tracer(){}

