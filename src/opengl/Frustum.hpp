#ifndef VOXELS_FRUSTUM_HPP
#define VOXELS_FRUSTUM_HPP

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

enum FrustumSide
{
    RIGHT = 0,
    LEFT = 1,
    BOTTOM = 2,
    TOP = 3,
    BACK = 4,
    FRONT = 5
};

enum PlaneData
{
    A = 0,
    B = 1,
    C = 2,
    D = 3
};

class Frustum
{
private:
    float m_Frustum[6][4];
public:
    Frustum();
    void CalculateFrustum(const glm::mat4& projMatrix, const glm::mat4& viewMatrix);
    bool PointInFrustum(float x, float y, float z);
    bool SphereInFrustum(float x, float y, float z, float radius);
    bool CubeInFrustum(float x, float y, float z, float width, float height, float depth);
    bool CubeInFrustum(const glm::vec3& pos, const glm::vec3& dim);
    // bool CubeInFrustum(glm::vec3& pos, AABB& aabb);
    ~Frustum();
};


#endif //VOXELS_FRUSTUM_HPP
