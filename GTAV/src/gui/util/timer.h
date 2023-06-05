#pragma once
#include "pch.h"

class Timer
{
public:
    explicit Timer(std::chrono::milliseconds delay) :
        m_Timer(std::chrono::high_resolution_clock::now()),
        m_Delay(delay)
    {
    }

    bool Update() {
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_Timer) >= m_Delay)
        {
            m_Timer = now;
            return true;
        }

        return false;
    }

    void SetDelay(std::chrono::milliseconds delay) {
        m_Delay = delay;
    }

    std::chrono::milliseconds GetDelay() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_Delay);
    }


    void Reset() {
        m_Timer = std::chrono::high_resolution_clock::now();
    }

private:
    std::chrono::high_resolution_clock::time_point m_Timer;
    std::chrono::milliseconds m_Delay;
};