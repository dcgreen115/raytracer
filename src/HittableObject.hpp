//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_HITTABLEOBJECT_HPP
#define RAYTRACER_HITTABLEOBJECT_HPP

#include <memory>
#include "Ray.hpp"

class Material;

struct HitRecord {
    Point3 p;
    Vec3 normal;
    std::shared_ptr<Material> materialPtr;
    double t = 0;
    bool isFrontFace = false;

    // After running this function, a hit record's normal vector will always face
    // outward from the surface
    void setFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
        isFrontFace = Vec3::dot(ray.direction(), outwardNormal) < 0;
        normal = isFrontFace ? outwardNormal : -outwardNormal;
    }
};

class HittableObject {
public:
    virtual bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
};

#endif //RAYTRACER_HITTABLEOBJECT_HPP
