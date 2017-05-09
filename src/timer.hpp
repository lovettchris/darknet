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
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
    double start_;
    double end_;
};
