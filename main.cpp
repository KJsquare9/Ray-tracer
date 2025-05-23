#include "rtweekend.h"

#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#include "mesh.h"
#include <fstream>

int main(int argc, char* argv[]) {
    hittable_list world;

    // Add a ground sphere (keeping this for the "floor")
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    
    // Check if an OFF file path was provided as command line argument
    if (argc > 1) {
        std::string off_file = argv[1];
        // Load the OFF model and place it at coordinates (0, 0, -1) with scale 0.5
        // Adjusted position to center of view since sphere is removed
        world.add(make_shared<mesh>(off_file, point3(0, 0, -1), 0.5));
    } else {
        std::cerr << "Error: Please provide an OFF file path as an argument." << std::endl;
        std::cerr << "Usage: ./raytracer path/to/model.off" << std::endl;
        return 1;
    }
    
    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    
    // Instead of directly writing to standard output, create a specific file
    std::ofstream output_file("image.ppm");
    if (!output_file) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }
    
    // Set the output stream for the camera to use
    cam.render(world, output_file);
    
    output_file.close();
    std::cout << "Image saved to image.ppm" << std::endl;
    
    return 0;
}