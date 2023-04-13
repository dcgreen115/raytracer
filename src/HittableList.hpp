//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_HITTABLELIST_HPP
#define RAYTRACER_HITTABLELIST_HPP

#include <vector>
#include <memory>
#include "HittableObject.hpp"

class HittableList: public HittableObject {
public:
    HittableList() = default;
    explicit HittableList(const std::shared_ptr<HittableObject>& object);

    void clear();
    void add(const std::shared_ptr<HittableObject>& object);
    bool hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;
private:
    std::vector<std::shared_ptr<HittableObject>> objects;
};

#endif //RAYTRACER_HITTABLELIST_HPP
