#ifndef VOXELS_TIMER_HPP
#define VOXELS_TIMER_HPP

#include <iostream>

using Clock = std::chrono::high_resolution_clock;
using MilliSeconds = std::chrono::milliseconds;

class Timer
{
private:
    double lastLoopTime;
    float timeCount;
    int fps;
    int fpsCount;
    int ups;
    int upsCount;

public:
    Timer() = default;
    ~Timer() = default;

    void init();
    const double getTime();
    float getDelta();
    void updateFPS();
    void updateUPS();
    void update();
    int getFPS();
    int getUPS();
};


#endif //VOXELS_TIMER_HPP
