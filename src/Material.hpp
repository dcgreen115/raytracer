//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include "Ray.hpp"
#include "HittableObject.hpp"
#include "Color.hpp"

class Material {
public:
    virtual bool scatter(const Ray& rIn, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian: public Material {
public:
    explicit Lambertian(const Color& a): albedo(a) {};

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        auto scatterDirection = rec.normal + Vec3::randomUnitVector();

        // Catch degenerate scatter direction
        if (scatterDirection.nearZero()) {
            scatterDirection = rec.normal;
        }

        scattered = Ray(rec.p, scatterDirection);
        attenuation = albedo;
        return true;
    };

private:
    Color albedo;
};

class Metal: public Material {
public:
    explicit Metal(const Color& a): albedo(a) {};

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        Vec3 reflected = Vec3::reflect(Vec3::unitVector(rayIn.direction()), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return Vec3::dot(scattered.direction(), rec.normal) > 0;
    }

private:
    Color albedo;
};
#endif //RAYTRACER_MATERIAL_HPP
