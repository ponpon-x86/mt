#pragma once

#include <random>
#include <iostream>
#include <ctime>

class RNG {
public:
    RNG();
    ~RNG() = default;

    double generate();
    double generateDouble();
    int generateInt();
    int generateInt4bit();
private:
    std::uniform_real_distribution<double> dist_double; // (min, max)   
    std::mt19937 rng_double;
    
    // i guess i'll at least make a wider range
    std::uniform_int_distribution<int> dist_int; 
    std::mt19937 rng_int;

    std::uniform_int_distribution<int> dist_int_4bit; 
    std::mt19937 rng_int_4bit;
};