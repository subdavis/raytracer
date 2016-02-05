#ifndef ROOM_H
#define ROOM_H
#include "Ray.h"
#include "Vector3.h"
#include "Drawable.h"
#include "Light.h"
#include "Color.h"
#include <vector>
using std::vector;

class Room
{
public:
    Room(Ray cam, Vector3 top_l, Vector3 top_r, Vector3 bottom_l, Color bg);
    ~Room();
    void addObject(Drawable*obj);
    void addLight(Light l);
    
    vector<Drawable*> objs;
    vector<Light> lights;
    Ray* find_pixel_points(int width, int height);
    Color bg;
    Ray cam;
    
private:
    Vector3 bottom_l;
    Vector3 top_r;
    Vector3 top_l;
};

#endif // ROOM_H
