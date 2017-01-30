#ifndef VOXELS_SIMPLEXNOISE_HPP
#define VOXELS_SIMPLEXNOISE_HPP


/** \file
    \brief Declares the SimplexNoise class for producing Perlin simplex noise.
    \author Stefan Gustavson (stegu@itn.liu.se)
*/

/*
 * This is a clean, fast, modern and free Perlin Simplex noise class in C++.
 * Being a stand-alone class with no external dependencies, it is
 * highly reusable without source code modifications.
 *
 *
 * Note:
 * Replacing the "float" type with "double" can actually make this run faster
 * on some platforms. A templatized version of SimplexNoise could be useful.
 */
class SimplexNoise
{
public:
    SimplexNoise() {}
    ~SimplexNoise() {}

    /** 1D, 2D, 3D and 4D float Perlin noise
     */
    static float noise(float x);
    static float noise(float x, float y);
    static float noise(float x, float y, float z);
    static float noise(float x, float y, float z, float w);

    /** 1D, 2D, 3D and 4D float Perlin noise, with a specified integer period
     */
    static float pnoise(float x, int px);
    static float pnoise(float x, float y, int px, int py);
    static float pnoise(float x, float y, float z, int px, int py, int pz);
    static float pnoise(float x, float y, float z, float w,
                         int px, int py, int pz, int pw);

private:
    static unsigned char perm[];
    static float grad(int hash, float x);
    static float grad(int hash, float x, float y);
    static float grad(int hash, float x, float y, float z);
    static float grad(int hash, float x, float y, float z, float t);
};


#endif //VOXELS_SIMPLEXNOISE_HPP
