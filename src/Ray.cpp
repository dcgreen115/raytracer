//
// Created by dylangreen on 4/11/23.
//

#include "Ray.hpp"

Point3 Ray::origin() const {
    return originPoint;
}

Vec3 Ray::direction() const {
    return directionVector;
}

Point3 Ray::at(double t) const {
    return originPoint + t*directionVector;
}
