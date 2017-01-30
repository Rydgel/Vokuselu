#ifndef VOXELS_INTERPOLATION_HPP
#define VOXELS_INTERPOLATION_HPP

#include <cmath>

class Interpolation
{
public:
    // x in [0,1]
    static inline float smoothCurve(float x)
    {
        return 6*x*x*x*x*x - 15*x*x*x*x + 10*x*x*x;
    }

    /*
        Linear interpolations
    */

    static inline float linearInterpolation(float x0, float x1, float t)
    {
        return x0 + (x1 - x0) * t;
    }

    static float biLinearInterpolation(
            const float x0y0, const float x1y0,
            const float x0y1, const float x1y1,
            const float x, const float y);

    static float triLinearInterpolation(
            const float v000, const float v100, const float v010, const float v110,
            const float v001, const float v101, const float v011, const float v111,
            const float x, const float y, const float z);

    /*
        Cubic interpolations
    */

    static float cubicInterpolation(float x0, float x1, float x2, float x3, float t);
    static float biCubicInterpolation(float x0y[4], float x1y[4], float x2y[4], float x3y[4], float x);
};


#endif //VOXELS_INTERPOLATION_HPP
