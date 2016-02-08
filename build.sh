mkdir -p Build
mkdir -p Images
g++  -c  "main.cpp" -g -O0 -Wall  -o ./Build/main.cpp.o -I. -I.
g++  -c  "Vector3.cpp" -g -O0 -Wall  -o ./Build/Vector3.cpp.o -I. -I.
g++  -c  "Ray.cpp" -g -O0 -Wall  -o ./Build/Ray.cpp.o -I. -I.
g++  -c  "Light.cpp" -g -O0 -Wall  -o ./Build/Light.cpp.o -I. -I.
g++  -c  "Color.cpp" -g -O0 -Wall  -o ./Build/Color.cpp.o -I. -I.
g++  -c  "Room.cpp" -g -O0 -Wall  -o ./Build/Room.cpp.o -I. -I.
g++  -c  "Sphere.cpp" -g -O0 -Wall  -o ./Build/Sphere.cpp.o -I. -I.
g++  -c  "Plane.cpp" -g -O0 -Wall  -o ./Build/Plane.cpp.o -I. -I.
g++  -c  "Renderer.cpp" -g -O0 -Wall  -o ./Build/Renderer.cpp.o -I. -I.
g++  -c  "Tracer.cpp" -g -O0 -Wall  -o ./Build/Tracer.cpp.o -I. -I.
g++  -c  "PhongProp.cpp" -g -O0 -Wall  -o ./Build/PhongProp.cpp.o -I. -I.
g++ -o ./Build/RayTracer ./Build/main.cpp.o ./Build/Vector3.cpp.o ./Build/Ray.cpp.o ./Build/Light.cpp.o ./Build/Color.cpp.o ./Build/Room.cpp.o ./Build/Sphere.cpp.o ./Build/Plane.cpp.o ./Build/Renderer.cpp.o ./Build/Tracer.cpp.o ./Build/PhongProp.cpp.o -L.
echo "<<============================================================>>"
echo "   Build completed"
echo "   If the build was successful, you may run ./run.sh"
echo "   If there were errors, please retry on Ubuntu-based linux"
echo "<<============================================================>>"