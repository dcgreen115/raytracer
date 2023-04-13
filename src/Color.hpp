//
// Created by dylangreen on 4/11/23.
//

#ifndef RAYTRACER_COLOR_HPP
#define RAYTRACER_COLOR_HPP

#include <iostream>
#include "Vec3.hpp"

class Color: public Vec3 {
public:
    Color(double x, double y, double z);

    static void writeColor(std::ostream& out, Color pixelColor, int samplesPerPixel);

private:
    static double clamp(double x, double min, double max);
};

#endif //RAYTRACER_COLOR_HPP
