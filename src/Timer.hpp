#ifndef VOXELS_TIMER_HPP
#define VOXELS_TIMER_HPP

#include <iostream>
#include <GLFW/glfw3.h>


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
    void init();
    const double getTime();
    float getDelta();
    void updateFPS();
    void updateUPS();
    void update();
    int getFPS();
    int getUPS();
    ~Timer() = default;
};


#endif //VOXELS_TIMER_HPP
