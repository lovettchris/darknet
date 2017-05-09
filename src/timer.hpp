#pragma once

#include <chrono>
class Timer {
public:
    Timer() {

    }
    void start() {
        start_ = now();
    }
    void end() {
        end_ = now();
    }
    double seconds() {
        return end_ - start_;
    }
private:
    double now() {
        return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 1000000.0;
    }
    double start_;
    double end_;
};
