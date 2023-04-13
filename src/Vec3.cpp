//
// Created by dylangreen on 4/11/23.
//

#include <cmath>
#include "Vec3.hpp"
#include "util.hpp"

Vec3::Vec3(double x, double y, double z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

double Vec3::x() const {
    return data[0];
}

double Vec3::y() const {
    return data[1];
}

double Vec3::z() const {
    return data[2];
}

double Vec3::operator[](std::size_t i) const {
    return data[i];
}

double &Vec3::operator[](std::size_t i) {
    return data[i];
}

Vec3 Vec3::operator-() const {
    return {-data[0], -data[1], -data[2]};
}

Vec3 &Vec3::operator+=(const Vec3 &other) {
    data[0] += other.x();
    data[1] += other.y();
    data[2] += other.z();
    return *this;
}

Vec3 &Vec3::operator*=(double n) {
    data[0] *= n;
    data[1] *= n;
    data[2] *= n;
    return *this;
}

Vec3 &Vec3::operator/=(double n) {
    return *this *= 1/n;
}

double Vec3::magnitude() const {
    return sqrt(data[0]*data[0] + data[1]*data[1] + data[2]*data[2]);
}

std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z()};
}

Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z()};
}

Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return {v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z()};
}

Vec3 operator*(double n, const Vec3 &v) {
    return {v.x() * n, v.y() * n, v.z() * n};
}

Vec3 operator*(const Vec3 &v, double n) {
    return n * v;
}

Vec3 operator/(const Vec3 &v, double n) {
    return (1/n) * v;
}

double Vec3::dot(const Vec3 &v1, const Vec3 &v2) {
    return v1.x() * v2.x()
         + v1.y() * v2.y()
         + v1.z() * v2.z();
}

Vec3 Vec3::cross(const Vec3 &v1, const Vec3 &v2) {
    return {v1.y() * v2.z() - v1.z() * v2.y(),
                v1.z() * v2.x() - v1.x() * v2.z(),
                v1.x() * v2.y() - v1.y() * v2.x()};
}

Vec3 Vec3::unitVector(const Vec3 &v) {
    return v / v.magnitude();
}

Vec3 Vec3::random() {
    return {util::randomDouble(), util::randomDouble(), util::randomDouble()};
}

Vec3 Vec3::random(double min, double max) {
    return {util::randomDouble(min, max), util::randomDouble(min, max), util::randomDouble(min, max)};
}

Vec3 Vec3::randomInUnitSphere() {
    while (true) {
        auto p = random(-1, 1);
        if (p.magnitude() >= 1) continue;
        return p;
    }
}

Vec3 Vec3::randomUnitVector() {
    return unitVector(randomInUnitSphere());
}

Vec3 Vec3::randomInHemisphere(const Vec3 &normal) {
    Vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0) {
        return inUnitSphere;
    } else {
        return -inUnitSphere;
    }
}

bool Vec3::nearZero() const {
    // Return true if the vector is close to zero in all dimensions
    const auto s = 1e-8;
    return fabs(x()) < s &&  fabs(y()) < s && fabs(z()) < s;
}

Vec3 Vec3::reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2*dot(v, n)*n;
}

Vec3 Vec3::refract(const Vec3 &uv, const Vec3 &n, double etaiOverEtat) {
    auto cosTheta = fmin(dot(-uv, n), 1);
    Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta*n);
    Vec3 rOutParallel = -sqrt(fabs(1.0 - pow(rOutPerp.magnitude(), 2))) * n;
    return rOutPerp + rOutParallel;
}

Vec3 Vec3::randomInUnitDisk() {
    while (true) {
        auto p = Vec3(util::randomDouble(-1, 1), util::randomDouble(-1, 1), 0);
        if (p.magnitude() >= 1) continue;
        return p;
    }
}
