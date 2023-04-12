#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include "Color.hpp"
#include "Ray.hpp"

double hitSphere(const Point3& center, double radius, const Ray& ray) {
    Vec3 vectorToCenter = ray.origin() - center;
    auto a = Vec3::dot(ray.direction(), ray.direction());
    auto b = 2.0 * Vec3::dot(vectorToCenter, ray.direction());
    auto c = Vec3::dot(vectorToCenter, vectorToCenter) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

Color rayColor(const Ray& ray) {
    auto t = hitSphere(Point3(0, 0, -1), 0.5, ray);
    if (t > 0.0) {
        Vec3 normal = Vec3::unitVector(ray.at(t) - Vec3(0, 0, -1));
        Vec3 colorTemporary = (0.5*Color(normal.x() + 1, normal.y() + 1, normal.z() + 1));
        return *((Color*) &colorTemporary);
    }

    Vec3 unitDirection = Vec3::unitVector(ray.direction());
    t = 0.5*(unitDirection.y() + 1.0);
    Vec3 vec =  (1.0 - t) * Color(1.0, 1.0, 1.0) + t*Color(0.5, 0.7, 1.0);
    return *((Color*) &vec);
}

int main() {

    // Image params
    const double aspectRatio = 16.0/9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspectRatio);

    // Camera params
    double viewportHeight = 2.0;
    double viewportWidth = aspectRatio * viewportHeight;
    double focalLength = 1.0;
    auto origin = Point3(0, 0, 0);
    auto widthVector = Vec3(viewportWidth, 0, 0);
    auto heightVector = Vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - widthVector / 2 - heightVector / 2 - Vec3(0, 0, focalLength);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto widthPercentage = double(i) / (image_width - 1);
            auto heightPercentage = double(j) / (image_height - 1);
            Ray r(origin, lowerLeftCorner + widthPercentage * widthVector + heightPercentage * heightVector - origin);
            Color pixel_color = rayColor(r);
            pixel_color.writeColor(std::cout);
        }
    }

    std::cerr << "\nDone.\n";
}