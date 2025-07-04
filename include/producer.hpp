#pragma once

#include <iostream>
#include <vector>

#include "bus.hpp"

class Producer : public Bus {
    public:
    
    Producer(Bus* bus_ptr);
    Producer(const Producer& other);
    Producer(Producer&& other);
    Producer& operator=(const Producer& other);
    Producer& operator=(Producer&& other);

    int produce();
    void start();

    private:

    Bus* bus_ptr;
    std::future<int> future;
    RNG rng;
};

Producer::Producer(Bus* bus_ptr) {
    this->bus_ptr = bus_ptr;
}

Producer::Producer(const Producer& other) {
    this->bus_ptr = other.bus_ptr;
}

Producer::Producer(Producer&& other):
    bus_ptr(std::move(other.bus_ptr)) {};

Producer& Producer::operator=(const Producer& other) {
    if (this != &other) {
        bus_ptr = other.bus_ptr;
    }
    return *this;
}

Producer& Producer::operator=(Producer&& other) {
    if (this != &other) {
        bus_ptr = std::move(other.bus_ptr);
    }
    return *this;
}

int Producer::produce() {
    while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(rng.generateInt4bit()));
        bus_ptr->push(rng.generateDouble());
    }
}

void Producer::start() {
    this->future = std::async(std::launch::async, [this]{ return produce(); });
}