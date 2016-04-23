CC=g++
CFLAGS_EXE=-Wall -O3 -I./Build
CFLAGS=-Wall -O3 -c
LINKER=-lGL -lglut -lGLU
OUTFILE=PA4
BUILDDIR=Build/
OBJECTS=Build/*.o
#Drawable.o Color.o Light.o Plane.o Ray.o Room.o Sphere.o Vector3.o Renderer.o Tracer.o PhongProp.o

default: PA4

PA4: PA4.o
	$(CC) $(CFLAGS_EXE) $(OBJECTS) -o $(OUTFILE) $(LINKER)	

PA4.o: Color.o Light.o Plane.o Ray.o Room.o Sphere.o Vector3.o Renderer.o Tracer.o PhongProp.o
	$(CC) $(CFLAGS) main.cpp -o  $(BUILDDIR)PA4.o $(LINKER)

Tracer.o: Light.o Tracer.h Ray.o Renderer.o Color.o Room.o
	#include "Drawable.h"
	#include "Light.h"
	#include "Renderer.h"
	#include "Ray.h"
	#include "Color.h"
	#include "Room.h"
	$(CC) $(CFLAGS) Tracer.cpp -o $(BUILDDIR)Tracer.o $(LINKER)

Sphere.o:  Ray.o Vector3.o Color.o PhongProp.o Sphere.h
	#include "Drawable.h" // Base class: Drawable
	#include "Ray.h"
	#include "Vector3.h"
	#include "Color.h"
	#include "PhongProp.h"
	$(CC) $(CFLAGS) Sphere.cpp -o $(BUILDDIR)Sphere.o $(LINKER)

Room.o: Ray.o Vector3.o Light.o Color.o Renderer.o Room.h
	#include "Ray.h"
	#include "Vector3.h"
	#include "Drawable.h"
	#include "Light.h"
	#include "Color.h"
	#include "Renderer.h"
	$(CC) $(CFLAGS) Room.cpp -o $(BUILDDIR)Room.o $(LINKER)

# Drawable.o: Ray.o Color.o PhongProp.o Vector3.o Drawable.h
# 	#include "Ray.h"
# 	#include "Color.h"
# 	#include "PhongProp.h"
# 	#include "Vector3.h"
# 	$(CC) $(CFLAGS) Drawable.h -o $(BUILDDIR)Drawable.o $(LINKER)

Plane.o : Vector3.o Color.o PhongProp.o Plane.h
	#include "Drawable.h" // Base class: Drawable
	#include "Vector3.h"
	#include "Color.h"
	#include "PhongProp.h"
	$(CC) $(CFLAGS) Plane.cpp -o $(BUILDDIR)Plane.o $(LINKER)

Light.o:  Color.o Vector3.o Light.h
	#include "Color.h" // Base class: Ray
	#include "Vector3.h"
	$(CC) $(CFLAGS) Light.cpp -o $(BUILDDIR)Light.o $(LINKER)

PhongProp.o: Vector3.o PhongProp.cpp PhongProp.h
	$(CC) $(CFLAGS) PhongProp.cpp -o $(BUILDDIR)PhongProp.o $(LINKER)

Ray.o: Vector3.o Ray.h
	$(CC) $(CFLAGS) Ray.cpp -o $(BUILDDIR)Ray.o $(LINKER)

Vector3.o: Vector3.cpp Vector3.h
	$(CC) $(CFLAGS) Vector3.cpp -o $(BUILDDIR)Vector3.o $(LINKER)

Renderer.o: Color.o Renderer.h
	#include "Color.h"
	$(CC) $(CFLAGS) Renderer.cpp -o $(BUILDDIR)Renderer.o $(LINKER)	

Color.o: Color.h
	$(CC) $(CFLAGS) Color.cpp -o $(BUILDDIR)Color.o $(LINKER)

Sphere.o: Sphere.cpp Sphere.h
	$(CC) $(CFLAGS) Sphere.cpp -o $(BUILDDIR)Sphere.o $(LINKER)	

clean:
	rm $(BUILDDIR)*
