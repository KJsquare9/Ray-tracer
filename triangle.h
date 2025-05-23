#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "vec3.h"

class triangle : public hittable {
  public:
    triangle(const point3& v0, const point3& v1, const point3& v2)
        : v0(v0), v1(v1), v2(v2) {
        // Calculate normal vector
        vec3 edge1 = v1 - v0;
        vec3 edge2 = v2 - v0;
        normal_vec = unit_vector(cross(edge1, edge2));
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        // Möller–Trumbore algorithm for ray-triangle intersection
        vec3 edge1 = v1 - v0;
        vec3 edge2 = v2 - v0;
        vec3 h = cross(r.direction(), edge2);
        double a = dot(edge1, h);

        // Ray parallel to triangle check
        if (a > -1e-8 && a < 1e-8)
            return false;

        double f = 1.0 / a;
        vec3 s = r.origin() - v0;
        double u = f * dot(s, h);
        
        if (u < 0.0 || u > 1.0)
            return false;
            
        vec3 q = cross(s, edge1);
        double v = f * dot(r.direction(), q);
        
        if (v < 0.0 || u + v > 1.0)
            return false;
            
        double t = f * dot(edge2, q);
        
        if (t < ray_t.min || t > ray_t.max)
            return false;
        
        rec.t = t;
        rec.p = r.at(t);
        rec.set_face_normal(r, normal_vec);
        
        return true;
    }

  private:
    point3 v0, v1, v2;   // Vertices of the triangle
    vec3 normal_vec;     // Normal vector of the triangle
};

#endif
