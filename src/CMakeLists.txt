cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(raytracer main.cpp
        Vec3.cpp Vec3.hpp
        Color.cpp Color.hpp
        Ray.cpp Ray.hpp
        HittableObject.hpp Sphere.cpp Sphere.hpp HittableList.cpp HittableList.hpp MainConstants.hpp Camera.cpp Camera.hpp)
