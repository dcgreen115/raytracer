//
// Created by dylangreen on 4/12/23.
//

#include "HittableList.hpp"

HittableList::HittableList(const std::shared_ptr<HittableObject>& object) {
    add(object);
}

void HittableList::clear() {
    objects.clear();
}

void HittableList::add(const std::shared_ptr<HittableObject>& object) {
    objects.push_back(object);
}

bool HittableList::hit(const Ray &ray, double tMin, double tMax, HitRecord &record) const {
    HitRecord tempRecord;
    bool rayHitAnything = false;
    double closestT = tMax;

    for (const auto& object : objects) {
        if (object->hit(ray, tMin, closestT, tempRecord) && tempRecord.t < closestT) {
            rayHitAnything = true;
            closestT = tempRecord.t;
            record = tempRecord;
        }
    }

    return rayHitAnything;
}
