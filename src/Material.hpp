//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP

#include <cmath>
#include "Ray.hpp"
#include "HittableObject.hpp"
#include "Color.hpp"
#include "util.hpp"

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
    explicit Metal(const Color& a, double fuzz): albedo(a), fuzziness(fuzz < 1 ? fuzz : 1) {};

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        Vec3 reflected = Vec3::reflect(Vec3::unitVector(rayIn.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzziness*Vec3::randomInUnitSphere());
        attenuation = albedo;
        return Vec3::dot(scattered.direction(), rec.normal) > 0;
    }

private:
    Color albedo;
    double fuzziness = 0;
};

class Dielectric: public Material {
public:
    explicit Dielectric(double ir): indexOfRefraction(ir) {};

    bool scatter(const Ray& rayIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        attenuation = Color(1, 1, 1);
        double refractionRatio = rec.isFrontFace ? (1.0/indexOfRefraction) : indexOfRefraction;

        Vec3 unitDirection = Vec3::unitVector(rayIn.direction());
        double cosTheta = fmin(Vec3::dot(-unitDirection, rec.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vec3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > util::randomDouble()) {
            direction = Vec3::reflect(unitDirection, rec.normal);
        } else {
            direction = Vec3::refract(unitDirection, rec.normal, refractionRatio);
        }

        scattered = Ray(rec.p, direction);
        return true;
    }

private:
    double indexOfRefraction = 1.0;

    static double reflectance(double cosine, double refIdx) {
        // Use Schlick's approximation for reflectance
        auto r0 = (1 - refIdx) / (1 + refIdx);
        r0 = r0*r0;
        return r0 + (1 - r0)*pow((1 - cosine), 5);
    }
};

#endif //RAYTRACER_MATERIAL_HPP
