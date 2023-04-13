//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_UTIL_HPP
#define RAYTRACER_UTIL_HPP

#include <limits>
#include <random>

namespace util {
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    double degreesToRadians(double degrees);
    double randomDouble();
    double randomDouble(double min, double max);
}

#endif //RAYTRACER_UTIL_HPP
