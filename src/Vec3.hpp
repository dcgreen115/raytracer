//
// Created by dylangreen on 4/11/23.
//

#ifndef RAYTRACER_VEC3_HPP
#define RAYTRACER_VEC3_HPP

#include <array>
#include <ostream>

class Vec3 {
public:
    Vec3() = default;
    Vec3(double x, double y, double z);

    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
    [[nodiscard]] double z() const;

    [[nodiscard]] double magnitude() const;

    double operator[](std::size_t i) const;
    double& operator[](std::size_t i);

    Vec3 operator-() const;
    Vec3& operator+=(const Vec3 &other);
    Vec3& operator*=(double n);
    Vec3& operator/=(double n);

    friend std::ostream& operator<<(std::ostream &out, const Vec3 &v);
    friend Vec3 operator+(const Vec3& v1, const Vec3& v2);
    friend Vec3 operator-(const Vec3& v1, const Vec3& v2);
    friend Vec3 operator*(const Vec3& v1, const Vec3& v2);
    friend Vec3 operator*(double n, const Vec3& v);
    friend Vec3 operator*(const Vec3& v, double n);
    friend Vec3 operator/(const Vec3& v, double n);

    static double dot(const Vec3& v1, const Vec3& v2);
    static Vec3 cross(const Vec3& v1, const Vec3& v2);
    static Vec3 reflect(const Vec3& v, const Vec3& n);
    static Vec3 refract(const Vec3& uv, const Vec3& n, double etaiOverEtat);
    static Vec3 unitVector(const Vec3& v);

    static Vec3 random();
    static Vec3 random(double min, double max);

    // Used for diffuse scattering
    static Vec3 randomInUnitSphere();
    static Vec3 randomUnitVector();
    static Vec3 randomInHemisphere(const Vec3& normal);
    static Vec3 randomInUnitDisk();

    [[nodiscard]] bool nearZero() const;

private:
    std::array<double, 3> data = {0, 0, 0};
};

typedef Vec3 Point3;

#endif //RAYTRACER_VEC3_HPP
