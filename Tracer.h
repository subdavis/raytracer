#ifndef TRACER_H
#define TRACER_H
#include "Room.h"
#include "Renderer.h"
#include "Ray.h"

class Tracer
{
public:
    Tracer(bool antialias, bool lighting, bool shadows);
    ~Tracer();
    void trace(Room *room, Renderer *renderer);
    bool antialias;
    bool lighting;
    bool shadows;
};

#endif // TRACER_H
