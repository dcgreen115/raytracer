cmake_minimum_required(VERSION 3.5)
project(raytracer)

set(CMAKE_CXX_STANDARD 23)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(raytracer main.cpp
        Vec3.cpp Vec3.hpp
        Color.cpp Color.hpp
        Ray.cpp Ray.hpp
        HittableObject.hpp
        Sphere.cpp Sphere.hpp
        HittableList.cpp HittableList.hpp
        Camera.cpp Camera.hpp
        util.cpp util.hpp
        Material.hpp)
