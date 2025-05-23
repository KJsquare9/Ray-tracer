#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <algorithm>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Custom clamp function (no std::clamp dependency)
template<typename T>
inline T clamp(const T& value, const T& min, const T& max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Vector and Ray headers first (no color.h dependency)
#include "vec3.h"
#include "ray.h"
#include "interval.h"

// Now we can include color.h which depends on vec3.h
#include "color.h"

#endif