#ifndef VOXELS_CHUNK_HPP
#define VOXELS_CHUNK_HPP

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Voxel.hpp"
#include "map/MapGeneratorHeightmap.hpp"

class MapGeneratorHeightmap;

class Chunk
{
public:
    static const int SIZE = 64;
private:
    int m_id;
    Voxel m_voxels[Chunk::SIZE][Chunk::SIZE][Chunk::SIZE];
    int m_xOffset;
    int m_yOffset;
    int m_zOffset;
    // we need to keep that in cache and recreate it at each
    // chunk edition (adding/removing a cube)
    std::vector<glm::vec4> m_positionsLayered;
    bool m_shouldRegen = true;
    std::unique_ptr<MapGeneratorHeightmap> m_mapGen;

    int getVoxelType(int x, int y, int z);
public:
    Chunk(int id, int xOffset, int yOffset, int zOffset);
    void generateCubesPositions();
    std::vector<glm::vec4> getCubesPositions();
    void setShouldRegen();
    void fill(Voxel voxel, int x, int y, int z);
    glm::vec3 getChunkOffset();
    ~Chunk();
};


#endif //VOXELS_CHUNK_HPP
