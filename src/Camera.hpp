//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 vUp, double vfov, double aspectRatio, double aperture, double focusDist);

    [[nodiscard]] Ray getRay(double s, double t) const;

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontalVector;
    Vec3 verticalVector;
    Vec3 w, u, v;
    double lensRadius = 1.0;
};

#endif //RAYTRACER_CAMERA_HPP
