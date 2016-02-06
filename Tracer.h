#ifndef TRACER_H
#define TRACER_H
#include "Room.h"
#include "Renderer.h"
#include "Ray.h"
#include "Color.h"

class Tracer
{
public:
    Tracer(bool antialias, bool lighting, bool shadows);
    ~Tracer();
    void trace(Room *room, Renderer *renderer);
    Color recursive_trace(Ray start_ray);
    bool antialias;
    bool lighting;
    bool shadows;
};

#endif // TRACER_H
