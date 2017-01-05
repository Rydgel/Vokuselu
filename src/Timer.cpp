#include "Timer.hpp"

void Timer::init()
{
    m_lastLoopTime = getTime();
    m_timeCount = 0.0;
    m_fps = 0;
    m_fpsCount = 0;
    m_ups = 0;
    m_upsCount = 0;
}

const double Timer::getTime()
{
    auto duration = Clock::now().time_since_epoch();
    auto getMs = std::chrono::duration_cast<MilliSeconds>(duration).count();
    return getMs / 1000.0;
}

const float Timer::getDelta()
{
    double time = getTime();
    float delta = (float) (time - m_lastLoopTime);
    m_lastLoopTime = time;
    m_timeCount += delta;
    return delta;
}

void Timer::updateFPS()
{
    m_fpsCount ++;
}

void Timer::updateUPS()
{
    m_upsCount ++;
}

void Timer::update()
{
    if (m_timeCount > 1.0) {
        m_fps = m_fpsCount;
        m_fpsCount = 0;

        m_ups = m_upsCount;
        m_upsCount = 0;

        m_timeCount -= 1.0;
    }
}

int Timer::getFPS()
{
    return m_fps > 0 ? m_fps : m_fpsCount;
}

int Timer::getUPS()
{
    return m_ups > 0 ? m_ups : m_upsCount;
}
