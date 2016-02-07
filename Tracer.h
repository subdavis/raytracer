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
    int objs_tocheck;
    int lights_tocheck;
    int depth;
};

#endif // TRACER_H
