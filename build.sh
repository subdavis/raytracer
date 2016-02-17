mkdir -p Build
mkdir -p Images
FLAGS="-g -O2 -Wall -o"
g++  -c  "main.cpp" $FLAGS ./Build/main.cpp.o -I. 
g++  -c  "Vector3.cpp" $FLAGS ./Build/Vector3.cpp.o -I. 
g++  -c  "Ray.cpp" $FLAGS ./Build/Ray.cpp.o -I. 
g++  -c  "Light.cpp" $FLAGS ./Build/Light.cpp.o -I.
g++  -c  "Color.cpp" $FLAGS ./Build/Color.cpp.o -I.
g++  -c  "Room.cpp" $FLAGS ./Build/Room.cpp.o -I.
g++  -c  "Sphere.cpp" $FLAGS ./Build/Sphere.cpp.o -I.
g++  -c  "Plane.cpp" $FLAGS ./Build/Plane.cpp.o -I.
g++  -c  "Renderer.cpp" $FLAGS ./Build/Renderer.cpp.o -I.
g++  -c  "Tracer.cpp" $FLAGS ./Build/Tracer.cpp.o -I.
g++  -c  "PhongProp.cpp" $FLAGS ./Build/PhongProp.cpp.o -I.
g++ -o ./Build/RayTracer ./Build/main.cpp.o ./Build/Vector3.cpp.o ./Build/Ray.cpp.o ./Build/Light.cpp.o ./Build/Color.cpp.o ./Build/Room.cpp.o ./Build/Sphere.cpp.o ./Build/Plane.cpp.o ./Build/Renderer.cpp.o ./Build/Tracer.cpp.o ./Build/PhongProp.cpp.o -L.

echo "<<============================================================>>"
echo "   Build completed"
echo "   If the build was successful, you may run ./run.sh"
echo "   If there were errors, please retry on ubuntu-based linux"
echo "<<============================================================>>"