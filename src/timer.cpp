#include "timer.h"

Timer::Timer() = default;

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
    running = true;
}

void Timer::stop() {
    end_time = std::chrono::high_resolution_clock::now();
    running = false;
}

double Timer::elapsedMilliseconds() const {
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    if(running) {
        endTime = std::chrono::high_resolution_clock::now();
    } else {
        endTime = end_time;
    }

    return std::chrono::duration<double, std::milli>(endTime - start_time).count();
}

double Timer::elapsedSeconds() const {
    return elapsedMilliseconds() / 1000.0;
}
