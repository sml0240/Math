#pragma once
#include <chrono>

template <class T1, class T2>
class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_Clock;

public:
    Timer() : m_Clock(std::chrono::high_resolution_clock::now()) { }
    void Reset() { m_Clock = std::chrono::high_resolution_clock::now(); }
    float Elapsed() const { return std::chrono::duration_cast<std::chrono::duration<T1, T2>>(std::chrono::high_resolution_clock::now() - m_Clock).count(); }
};