#include "Timer.hpp"

void Timer::init()
{
    lastLoopTime = getTime();
    timeCount = 0.0;
    fps = 0;
    fpsCount = 0;
    ups = 0;
    upsCount = 0;
}

const double Timer::getTime()
{
    auto duration = Clock::now().time_since_epoch();
    auto getMs = std::chrono::duration_cast<MilliSeconds>(duration).count();
    return getMs / 1000.0;
}

float Timer::getDelta()
{
    double time = getTime();
    float delta = (float) (time - lastLoopTime);
    lastLoopTime = time;
    timeCount += delta;
    return delta;
}

void Timer::updateFPS()
{
    fpsCount ++;
}

void Timer::updateUPS()
{
    upsCount ++;
}

void Timer::update()
{
    if (timeCount > 1.0) {
        fps = fpsCount;
        fpsCount = 0;

        ups = upsCount;
        upsCount = 0;

        timeCount -= 1.0;
    }
}

int Timer::getFPS()
{
    return fps > 0 ? fps : fpsCount;
}

int Timer::getUPS()
{
    return ups > 0 ? ups : upsCount;
}
