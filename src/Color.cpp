//
// Created by dylangreen on 4/11/23.
//

#include <cmath>
#include "Color.hpp"

Color::Color(double x, double y, double z) : Vec3(x, y, z) {}

void Color::writeColor(std::ostream &out, Color pixelColor, int samplesPerPixel) {
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Divide the color by the number of samples and gamma-correct for gamma = 2.0
    auto scale = 1.0 / samplesPerPixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0, 255] value of each color component
    out << static_cast<uint32_t>(256 * clamp(r, 0, 0.999)) << ' '
        << static_cast<uint32_t>(256 * clamp(g, 0, 0.999)) << ' '
        << static_cast<uint32_t>(256 * clamp(b, 0, 0.999)) << '\n';
}

double Color::clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
