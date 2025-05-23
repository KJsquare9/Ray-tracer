CXX = g++
CXXFLAGS = -std=c++11 -Wall -I..

raytracer: main.cpp vec3.h ray.h color.h hittable.h hittable_list.h interval.h camera.h sphere.h triangle.h mesh.h rtweekend.h ../OFFReader.h
	$(CXX) $(CXXFLAGS) main.cpp -o raytracer

clean:
	rm -f raytracer
