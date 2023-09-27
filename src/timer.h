#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
    bool running = false;

public:
    Timer();
    void start();
    void stop();
    double elapsedMilliseconds() const;
    double elapsedSeconds() const;
};
