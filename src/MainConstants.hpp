//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_MAINCONSTANTS_HPP
#define RAYTRACER_MAINCONSTANTS_HPP

#include <limits>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

double degreesToRadians(double degrees) {
    return degrees * pi / 180.0;
}

double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator(time(nullptr));
    return distribution(generator);
}

double randomDouble(double min, double max) {
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator(time(nullptr));
    return distribution(generator);
}

#endif //RAYTRACER_MAINCONSTANTS_HPP
