#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "HittableObject.hpp"
#include "MainConstants.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

Color rayColor(const Ray& ray, const HittableObject& world) {
    HitRecord record;
    if (world.hit(ray, 0, infinity, record)) {
        auto tempColor =  0.5 * (record.normal + Color(1, 1, 1));
        return *((Color*) &tempColor);
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

    // World setup
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

    // Camera
    Camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++) {
                auto u = (i + randomDouble()) / (image_width - 1);
                auto v = (j + randomDouble()) / (image_height - 1);
                Ray r = cam.getRay(u, v);
                pixelColor += rayColor(r, world);
            }
            Color::writeColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}