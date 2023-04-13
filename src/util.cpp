//
// Created by dylangreen on 4/12/23.
//

#include "util.hpp"

namespace util {
    double degreesToRadians(double degrees) {
        return degrees * pi / 180.0;
    }

    double randomDouble() {
        static std::default_random_engine generator{std::random_device{}()};
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return distribution(generator);
    }

    double randomDouble(double min, double max) {
        static std::default_random_engine generator{std::random_device{}()};
        std::uniform_real_distribution<double> distribution(min, max);
        return distribution(generator);
    }
}