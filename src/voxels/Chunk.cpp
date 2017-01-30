#include "Chunk.hpp"

Chunk::Chunk()
{

}

int Chunk::getVoxelType(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0) {
        return - 1;
    } else if (x > 15 || y > 15 || z > 15) {
        return -1;
    } else {
        return m_voxels[x][y][z].type;
    }
}

void Chunk::initChunk(int xOffset, int yOffset, int zOffset)
{
    m_xOffset = xOffset;
    m_yOffset = yOffset;
    m_zOffset = zOffset;

    for (int x = 0; x < 16; x ++) {
        for (int y = 0; y < 16; y ++) {
            for (int z = 0; z < 16; z ++) {
                if (x % 2 == 0) {
                    m_voxels[x][y][z] = Voxel { 0 };
                } else {
                    m_voxels[x][y][z] = Voxel { 3 };
                }
            }
        }
    }
}

void Chunk::generateCubesPositions()
{
    m_positionsLayered.clear();
    for (int x = 0; x < 16; x ++) {
        for (int y = 0; y < 16; y++) {
            for (int z = 0; z < 16; z++) {
                auto voxel = m_voxels[x][y][z];
                auto layout = voxel.type;

                if (layout == -1) {
                    // it's air
                    continue;
                }

                if (getVoxelType(x-1, y, z) != -1
                    && getVoxelType(x+1, y, z) != -1
                    && getVoxelType(x, y-1, z) != -1
                    && getVoxelType(x, y+1, z) != -1
                    && getVoxelType(x, y, z-1) != -1
                    && getVoxelType(x, y, z+1) != -1) {
                    // skip this block
                    continue;
                }

                m_positionsLayered.push_back(
                        glm::vec4(x + m_xOffset, y + m_yOffset, z + m_zOffset, layout)
                );
            }
        }
    }

    // don't return cubes that are not visible
    m_shouldRegen = false;
}

std::vector<glm::vec4> Chunk::getCubesPositions()
{
    if (m_shouldRegen) {
        generateCubesPositions();
    }

    return m_positionsLayered;
}

void Chunk::setShouldRegen()
{
    m_shouldRegen = true;
}

Chunk::~Chunk()
{

}