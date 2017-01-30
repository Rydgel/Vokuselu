#ifndef VOXELS_CHUNK_HPP
#define VOXELS_CHUNK_HPP

#include <vector>
#include <glm/vec4.hpp>
#include "Voxel.hpp"

class Chunk
{
private:
    Voxel m_voxels[16][16][16];
    int m_xOffset;
    int m_yOffset;
    int m_zOffset;
    // we need to keep that in cache and recreate it at each
    // chunk edition (adding/removing a cube)
    std::vector<glm::vec4> m_positionsLayered;
    bool m_shouldRegen = true;

    int getVoxelType(int x, int y, int z);
public:
    Chunk();
    void initChunk(int xOffset, int yOffset, int zOffset);
    void generateCubesPositions();
    std::vector<glm::vec4> getCubesPositions();
    void setShouldRegen();
    ~Chunk();
};


#endif //VOXELS_CHUNK_HPP
