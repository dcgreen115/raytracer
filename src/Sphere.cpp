//
// Created by dylangreen on 4/12/23.
//

#include <cmath>
#include "Sphere.hpp"

bool Sphere::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
    Vec3 originToCenter = ray.origin() - center;
    auto a = pow(ray.direction().magnitude(), 2);
    auto halfB = Vec3::dot(originToCenter, ray.direction());
    auto c = pow(originToCenter.magnitude(), 2) - radius*radius;

    auto discriminant = halfB*halfB - a*c;
    if (discriminant < 0) {
        return false;
    }

    auto sqrtD = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range
    auto root = (-halfB - sqrtD) / a;
    if (root < tMin || root > tMax) {
        root = (-halfB + sqrtD) / a;
        if (root < tMin || root < tMax) {
            return false;
        }
    }

    record.t = root;
    record.p = ray.at(root);
    Vec3 outwardNormal = (record.p - center) / radius;
    record.setFaceNormal(ray, outwardNormal);
    record.materialPtr = material;
    return true;
}
