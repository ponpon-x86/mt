#include "rng.hpp"

RNG::RNG() {
    dist = std::uniform_real_distribution<double>(-45., 45.); // (min, max)
    rng.seed(std::random_device{}());
}

double RNG::generate() {
    return dist(rng);
}