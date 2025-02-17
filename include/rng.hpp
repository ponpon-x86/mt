#pragma once

#include <random>
#include <iostream>
#include <ctime>

class RNG {
public:
    RNG();
    ~RNG() = default;

    double generate();
private:
    std::uniform_real_distribution<double> dist; // (min, max)   
    std::mt19937 rng;
};