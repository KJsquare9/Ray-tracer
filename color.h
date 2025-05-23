#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// Write the translated [0,255] value of each color component.
void write_color(std::ostream &out, color pixel_color) {
    // Write the RGB components with proper format, ensuring they are in the valid range
    int r = static_cast<int>(255.999 * clamp(pixel_color.x(), 0.0, 1.0));
    int g = static_cast<int>(255.999 * clamp(pixel_color.y(), 0.0, 1.0));
    int b = static_cast<int>(255.999 * clamp(pixel_color.z(), 0.0, 1.0));

    // Write the translated [0,255] value of each color component.
    out << r << ' ' << g << ' ' << b << '\n';
}

#endif