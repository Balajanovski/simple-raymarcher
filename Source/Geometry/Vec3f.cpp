// 
// Created by Balajanovski on 14/12/2017.
//

#include <cmath>
#include "Vec3f.h"

Vec3f::Vec3f(float x, float y, float z) {
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

Vec3f::Vec3f(const Vec3f &other) {
    data[0] = other.x();
    data[1] = other.y();
    data[2] = other.z();
}

Vec3f Vec3f::operator+(const Vec3f &rhs) const {
    return Vec3f(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
}

Vec3f Vec3f::operator+(float k) const {
    return Vec3f(x() + k, y() + k, z() + k);
}

Vec3f Vec3f::operator-(const Vec3f &rhs) const {
    return Vec3f(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
}

Vec3f Vec3f::operator-(float k) const {
    return Vec3f(x() - k, y() - k, z() - k);
}

Vec3f Vec3f::operator*(float k) const {
    return Vec3f(x() * k, y() * k, z() * k);
}

Vec3f Vec3f::operator*(const Vec3f &rhs) const {
    return Vec3f(x() * rhs.x(), y() * rhs.y(), z() * rhs.z());
}

Vec3f Vec3f::operator/(float k) const {
    return Vec3f(x() / k, y() / k, z() / k);
}

Vec3f Vec3f::operator%(float k) const {
    return Vec3f(x() - k * std::floor(x() / k), y() - k * std::floor(y() / k), z() - k * std::floor(z() / k));
}

float Vec3f::len() const {
    return sqrtf(dot(*this));
}

Vec3f Vec3f::normalize() const {
    if (len() == 0.0) {
        return *this;
    }
    return (*this / len());
}

float Vec3f::dot(const Vec3f &rhs) const {
    return (x() * rhs.x()) + (y() * rhs.y()) + (z() * rhs.z());
}

Vec3f Vec3f::cross(const Vec3f &rhs) const {
    return Vec3f(y() * rhs.z() - z() * rhs.y(),
                   z() * rhs.x() - x() * rhs.z(),
                   x() * rhs.y()- y() * rhs.x());
}

Vec3f Vec3f::reflect(const Vec3f &normal) const {
    return *this - normal * 2 * (*this * normal);
}

void Vec3f::make_positive() {
    for (int i = 0; i < 3; ++i) {
        data[i] = (data[i] < 0.0f) ? -data[i] : data[i];
    }
}

Vec3f min(const Vec3f& lhs, const Vec3f& rhs) {
    return Vec3f(fminf(lhs.x(), rhs.x()), fminf(lhs.y(), rhs.y()), fminf(lhs.z(), rhs.z()));
}

Vec3f max(const Vec3f& lhs, const Vec3f& rhs) {
    return Vec3f(fmaxf(lhs.x(), rhs.x()), fmaxf(lhs.y(), rhs.y()), fmaxf(lhs.z(), rhs.z()));
}

Vec3f abs(const Vec3f& vec) {
    return Vec3f(std::abs(vec.x()), std::abs(vec.y()), std::abs(vec.z()));
}