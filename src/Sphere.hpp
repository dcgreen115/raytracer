//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "HittableObject.hpp"

class Sphere: public HittableObject {
public:
    Sphere() = default;
    Sphere(Point3 cen, double r): center(cen), radius(r) {};

    bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

private:
    Point3 center;
    double radius = 0;
};

#endif //RAYTRACER_SPHERE_HPP
