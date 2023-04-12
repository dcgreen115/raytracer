//
// Created by dylangreen on 4/11/23.
//

#include <cmath>
#include "Vec3.hpp"

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
