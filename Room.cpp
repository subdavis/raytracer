#include "Room.h"
#include <cmath> 

Room::Room(Ray cam, Vector3 top_l, Vector3 top_r, Vector3 bottom_l, Color bg): 
cam(cam), top_l(top_l), top_r(top_r), bottom_l(bottom_l), bg(bg)
{
    std::vector<Drawable*> objs;
    std::vector<Light> lights;
}

void Room::addObject(Drawable *obj){
    objs.push_back(obj);
}

void Room::addLight(Light l){
    lights.push_back(l);
}

Ray* Room::find_pixel_points(int width, int height){
    
    //direction from left to right in view frame
    Vector3 v_right = top_r.minus(top_l);
    Vector3 u_right = v_right.Unit();
    //direction from top to bottom
    Vector3 v_down = bottom_l.minus(top_l);
    Vector3 u_down = v_down.Unit();
    //step scalars for each pixel
    double step_x = std::abs(v_right.Scale(1.0/width).Magnitude());
    double step_y = std::abs(v_down.Scale(1.0/height).Magnitude());
    
    Ray *rays = new Ray[width * height];
    
    //raster left to right, then top to bottom
    for (int j = 0; j < height; j++){
        for (int i = 0; i < width; i++){
            //Logic for getting new pixel point
            int dex = j * width + i;
            Vector3 xdiff = u_right.Scale(step_x * i + (step_x/2));
            Vector3 ydiff = u_down.Scale(step_y * j + (step_y/2));
            Vector3 p_new = top_l.add(xdiff).add(ydiff);
            rays[dex] = Ray(p_new, p_new.minus(cam.point).Unit());
        }
    }
    return rays;
}

Room::~Room()
{}

