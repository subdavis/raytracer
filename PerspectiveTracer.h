#ifndef PERSPECTIVETRACER_H
#define PERSPECTIVETRACER_H

#include "Tracer.h" // Base class: Tracer

class PerspectiveTracer : public Tracer
{
public:
    PerspectiveTracer(bool antialias, bool lighting);
    ~PerspectiveTracer();

};

#endif // PERSPECTIVETRACER_H
