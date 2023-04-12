//
// Created by dylangreen on 4/11/23.
//

#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "Vec3.hpp"

class Ray {
public:
    Ray() = default;
    Ray(const Point3& origin, const Vec3& direction): originPoint(origin), directionVector(direction) {}

    [[nodiscard]] Point3 origin() const;
    [[nodiscard]] Vec3 direction() const;

    [[nodiscard]] Point3 at(double t) const;

private:
    Point3 originPoint;
    Vec3 directionVector;
};

#endif //RAYTRACER_RAY_HPP
