//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include <memory>
#include <utility>
#include "HittableObject.hpp"

class Sphere: public HittableObject {
public:
    Sphere() = default;
    Sphere(Point3 cen, double r, std::shared_ptr<Material> m): center(cen), radius(r), material(std::move(m)){};

    bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

private:
    Point3 center;
    double radius = 0;
    std::shared_ptr<Material> material;
};

#endif //RAYTRACER_SPHERE_HPP
