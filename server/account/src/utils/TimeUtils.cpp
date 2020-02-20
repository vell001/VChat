//
// Created by vellhe on 2019-10-24.
//

#include "TimeUtils.h"

long long nowNs() {
    struct timespec time{0, 0};
    clock_gettime(CLOCK_REALTIME, &time);
    return (long long) time.tv_sec * 1000000000 + time.tv_nsec;
}

long long nowMs() {
    struct timespec time{0, 0};
    clock_gettime(CLOCK_REALTIME, &time);
    return (long long) time.tv_sec * 1000 + time.tv_nsec / 1000000;
}

double nowSec() {
    struct timespec time{0, 0};
    clock_gettime(CLOCK_REALTIME, &time);
    return time.tv_sec + time.tv_nsec / 1000000000.0;
}

void nowStr(std::string &str) {
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buffer[256];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H_%M_%S", std::localtime(&t));
    str = buffer;
}