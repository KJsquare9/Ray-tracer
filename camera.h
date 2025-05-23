#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "hittable_list.h"
#include "color.h"
#include "interval.h"

class camera {
  public:
    double aspect_ratio = 16.0 / 9.0;  
    int    image_width  = 800;  

    void render(const hittable& world, std::ostream& out = std::cout) {
        initialize();

        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                auto ray_direction = pixel_center - center;
                ray r(center, ray_direction);

                color pixel_color = ray_color(r, world, 0);
                write_color(out, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";
    }

  private:
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    point3 light_position = point3(5, 5, 5);  // Position of the light source
    int    max_depth = 5;  // Maximum reflection depth

    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world, int depth = 0) const {
        hit_record rec;

        // If we've exceeded the ray bounce limit, no more light is gathered
        if (depth >= max_depth)
            return color(0, 0, 0);

        if (world.hit(r, interval(0.001, infinity), rec)) {
            // Calculate shadow ray from hit point to light source
            vec3 direction_to_light = light_position - rec.p;
            double distance_to_light = direction_to_light.length();
            direction_to_light = unit_vector(direction_to_light);
            
            // Create shadow ray
            ray shadow_ray(rec.p + rec.normal * 0.001, direction_to_light);
            
            hit_record shadow_rec;
            bool in_shadow = world.hit(shadow_ray, interval(0.001, distance_to_light), shadow_rec);
            
            // Base color from normal
            color base_color = 0.5 * (rec.normal + color(1,1,1));
            
            // Calculate reflection ray
            vec3 reflected = reflect(r.direction(), rec.normal);
            ray reflection_ray(rec.p + rec.normal * 0.001, reflected);
            
            // Get color from reflection (recursive call with increased depth)
            color reflection_color = ray_color(reflection_ray, world, depth + 1);
            
            // Apply shadow and combine with reflection
            double reflectivity = 0.3; // Reflectivity factor (0.0 to 1.0)
            
            if (in_shadow) {
                return 0.2 * base_color + reflectivity * reflection_color;
            } else {
                // Calculate light intensity based on angle to light
                double light_intensity = std::max(0.2, dot(rec.normal, direction_to_light));
                return (1.0 - reflectivity) * light_intensity * base_color + reflectivity * reflection_color;
            }
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
    
    // Helper function to calculate reflection vector
    vec3 reflect(const vec3& v, const vec3& n) const {
        return v - 2 * dot(v, n) * n;
    }
};

#endif