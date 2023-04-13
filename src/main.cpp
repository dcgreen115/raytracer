#include <iostream>
#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "HittableObject.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "util.hpp"

Color rayColor(const Ray& ray, const HittableObject& world, int depth) {
    HitRecord record;

    // If we've exceeded the ray bounce limit, no more light is gathered
    if (depth <= 0) {
        return {0, 0, 0};
    }

    if (world.hit(ray, 0.001, util::infinity, record)) {
        //auto tempColor =  0.5 * (record.normal + Color(1, 1, 1));
        //return *((Color*) &tempColor);

        // Diffuse scattering
        // Random vector in unit sphere
        // Point3 target = record.p + record.normal + Vec3::randomInUnitSphere();

        // Random unit length vector
        // Point3 target = record.p + record.normal + Vec3::randomUnitVector();

        // Random vector in the same hemisphere as the normal
        //Point3 target = record.p + Vec3::randomInHemisphere(record.normal);

        // Using different materials
        Ray scattered;
        Color attenuation;
        if (record.materialPtr->scatter(ray, record, attenuation, scattered)) {
            auto tempColor = attenuation * rayColor(scattered, world, depth - 1);
            return *((Color*) &tempColor);
        } else {
            return {0, 0, 0};
        }
    }

    Vec3 unitDirection = Vec3::unitVector(ray.direction());
    auto t = 0.5*(unitDirection.y() + 1.0);
    auto tempColor =  (1.0 - t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
    return *((Color*) &tempColor);
}

int main() {

    // Image params
    const double aspectRatio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    // World setup
    HittableList world;
    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(Color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<Metal>(Color(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    Camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++) {
                auto u = (i + util::randomDouble()) / (image_width - 1);
                auto v = (j + util::randomDouble()) / (image_height - 1);
                Ray r = cam.getRay(u, v);
                pixelColor += rayColor(r, world, maxDepth);
            }
            Color::writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}