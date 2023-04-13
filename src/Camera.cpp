//
// Created by dylangreen on 4/12/23.
//

#include "Camera.hpp"
#include "Ray.hpp"

Camera::Camera() {
    auto aspectRatio = 16.0 / 9.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = aspectRatio * viewportHeight;
    auto focalLength = 1.0;

    origin = Point3(0, 0, 0);
    horizontalVector = Vec3(viewportWidth, 0, 0);
    verticalVector = Vec3(0, viewportHeight, 0);
    lowerLeftCorner = origin - horizontalVector/2 - verticalVector/2 - Vec3(0, 0, focalLength);
}

Ray Camera::getRay(double u, double v) const {
    return {origin, lowerLeftCorner + u*horizontalVector + v*verticalVector - origin};
}
