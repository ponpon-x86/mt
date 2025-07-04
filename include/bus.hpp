#pragma once

#include <vector>
#include <queue>
#include <mutex>

#include "misc.h"

class Bus {
    public:

    Bus() {};
    ~Bus() = default;

    void push(double item);
    double pop();

    private:

    std::queue<double> storage;
    std::mutex mutex;
    std::condition_variable cv;
};

void Bus::push(double item) {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]{ return storage.size() < 10; });

    storage.push(item);
    lock.unlock();
    cv.notify_one();
}

double Bus::pop() {
    if (storage.size() < 10) {
        cv.notify_one();
    }

    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this]{ return storage.size() > 0; });

    auto val = storage.front();
    storage.pop();

    lock.unlock();
    cv.notify_one();

    return val;
}