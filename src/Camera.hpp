//
// Created by dylangreen on 4/12/23.
//

#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {
public:
    Camera();

    [[nodiscard]] Ray getRay(double u, double v) const;

private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontalVector;
    Vec3 verticalVector;
};

#endif //RAYTRACER_CAMERA_HPP
