//
// Created by dylangreen on 4/11/23.
//

#include "Color.hpp"

Color::Color(double x, double y, double z) : Vec3(x, y, z) {}

void Color::writeColor(std::ostream &out) {
    out << static_cast<uint32_t>(255.999 * x()) << ' '
        << static_cast<uint32_t>(255.999 * y()) << ' '
        << static_cast<uint32_t>(255.999 * z()) << '\n';
}
