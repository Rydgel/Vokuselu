#include "Chunk.hpp"

Chunk::Chunk(int id, int xOffset, int yOffset, int zOffset)
{
    m_id = id;
    m_xOffset = xOffset;
    m_yOffset = yOffset;
    m_zOffset = zOffset;

    // todo find a better way :'(
    m_mapGen = std::make_unique<MapGeneratorHeightmap>(id);

    for (int x = 0; x < Chunk::SIZE; x ++) {
        for (int y = 0; y < Chunk::SIZE; y ++) {
            for (int z = 0; z < Chunk::SIZE; z ++) {
                m_voxels[x][y][z] = Voxel { VoxelType::DIRT };
                /*if (x % 2 == 0) {
                    m_voxels[x][y][z] = Voxel { VoxelType::DIRT };
                } else {
                    m_voxels[x][y][z] = Voxel { VoxelType::STONE };
                }*/
                // m_voxels[x][y][z] = Voxel { VoxelType::AIR };
            }
        }
    }

    // m_mapGen->makeChunk(*this);
}

int Chunk::getVoxelType(int x, int y, int z)
{
    if (x < 0 || y < 0 || z < 0) {
        return - 1;
    } else if (x >= Chunk::SIZE || y >= Chunk::SIZE || z >= Chunk::SIZE) {
        return -1;
    } else {
        return m_voxels[x][y][z].type;
    }
}

void Chunk::generateCubesPositions()
{
    m_positionsLayered.clear();
    for (int x = 0; x < Chunk::SIZE; x ++) {
        for (int y = 0; y < Chunk::SIZE; y++) {
            for (int z = 0; z < Chunk::SIZE; z++) {
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

void Chunk::fill(Voxel voxel, int x, int y, int z)
{
    m_voxels[x][y][z] = voxel;
    setShouldRegen();
}

glm::vec3 Chunk::getChunkOffset()
{
    return glm::vec3(m_xOffset, m_yOffset, m_zOffset);
}

Chunk::~Chunk()
{
    printf("Chunk %d deallocated\n", m_id);
}