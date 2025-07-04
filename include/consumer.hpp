#pragma once

#include "bus.hpp"

class Consumer {
    public:
    
    Consumer(Bus* bus_ptr);
    Consumer(const Consumer& other);
    Consumer(Consumer&& other);
    Consumer& operator=(const Consumer& other);
    Consumer& operator=(Consumer&& other);

    double consume();
    void start();

    private:

    Bus* bus_ptr;
    std::future<double> future;
};

Consumer::Consumer(Bus* bus_ptr) {
    this->bus_ptr = bus_ptr;
}

Consumer::Consumer(const Consumer& other) {
    this->bus_ptr = other.bus_ptr;
}

Consumer::Consumer(Consumer&& other) :
bus_ptr(std::move(other.bus_ptr)) {};

Consumer& Consumer::operator=(const Consumer& other) {
    if (this != &other) {
        bus_ptr = other.bus_ptr;
    }
    return *this;
}

Consumer& Consumer::operator=(Consumer&& other) {
    if (this != &other) {
        bus_ptr = std::move(other.bus_ptr);
    }
    return *this;
}

double Consumer::consume() {
    this->future = std::async(std::launch::async, [this] { return bus_ptr->pop(); });
    return future.get();
}

void Consumer::start() {
    while (1) {
        auto val = consume();
        std::cout << " > Consumer's ::consume() called. Retrieved: [" << val << "] <\n";
    }
}