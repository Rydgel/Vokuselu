#ifndef VOXELS_NOISE_HPP
#define VOXELS_NOISE_HPP


class Noise
{
public:
    static float noise2d(int x, int y, int seed);

    static float noise2dGradient(float x, float y, int seed);

    static float noise2dPerlin(
            float x, float y, int seed,
            int octaves, float persistence, float period);

    static float noise3d(int x, int y, int z, int seed);

    static float noise3dGradient(float x, float y, float z, int seed);

    static float noise3dPerlin(
            float x, float y, float z, int seed,
            int octaves, float persistence, float period);
};


#endif //VOXELS_NOISE_HPP
