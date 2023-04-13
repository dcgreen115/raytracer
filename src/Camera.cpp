//
// Created by dylangreen on 4/12/23.
//

#include "Camera.hpp"
#include "Ray.hpp"
#include "util.hpp"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp, double vfov, double aspectRatio, double aperture, double focusDist) {
    auto theta = util::degreesToRadians(vfov);
    auto h = tan(theta/2);
    auto viewportHeight = 2.0*h;
    auto viewportWidth = aspectRatio * viewportHeight;

    w = Vec3::unitVector(lookFrom - lookAt);
    u = Vec3::unitVector(Vec3::cross(vUp, w));
    v = Vec3::cross(w, u);

    origin = lookFrom;
    horizontalVector = focusDist * viewportWidth * u;
    verticalVector = focusDist * viewportHeight * v;
    lowerLeftCorner = origin - horizontalVector/2 - verticalVector/2 - focusDist * w;

    lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const {
    Vec3 rd = lensRadius * Vec3::randomInUnitDisk();
    Vec3 offset = u * rd.x() + v * rd.y();

    return {origin + offset,lowerLeftCorner + s*horizontalVector + t*verticalVector - origin - offset};
}
