#include "rng.hpp"

RNG::RNG() {
    dist_double = std::uniform_real_distribution<double>(-45., 45.); // (min, max)
    rng_double.seed(std::random_device{}());

    dist_int = std::uniform_int_distribution<int>(-200, 200); // (min, max) 
    rng_int.seed(std::random_device{}());

    dist_int_4bit = std::uniform_int_distribution<int>(0, 3);
    rng_int_4bit.seed(std::random_device{}());
}

double RNG::generate() {
    return dist_double(rng_double);
}

double RNG::generateDouble() {
    return dist_double(rng_double);
}

int RNG::generateInt() {
    return dist_int(rng_int);
}

int RNG::generateInt4bit() {
    return dist_int_4bit(rng_int_4bit);
}