#ifndef TRACER_H
#define TRACER_H
#include "Room.h"
#include "Renderer.h"
#include "Ray.h"
#include "Color.h"

class Tracer
{
public:
    Tracer(bool lighting, bool falloff);
    ~Tracer();
    void trace(Room *room, Renderer *renderer);
    Color recursive_trace(Ray start_ray, Room *room, Renderer *r);
    bool antialias;
    bool lighting;
    bool falloff;
    int sample_index;
    //Some data the recursive tracer needs
    int num_objects;
    int num_lights;
    int depth;
    int max_depth;
};

#endif // TRACER_H
