#include "MapGeneratorHeightmap.hpp"


MapGeneratorHeightmap::MapGeneratorHeightmap(int seed)
: MapGenerator(seed)
{
    m_seed = seed;
}

void MapGeneratorHeightmap::makeChunk(Chunk &chunk)
{
    auto org = chunk.getChunkOffset();

    // Generates a simple heightmap
    if (org.z >= -96 && org.z < 160) {
        for (int y = 0; y < 16; y++)
            for (int x = 0; x < 16; x++) {
                int h = abs((int) (256.f * Noise::noise2dPerlin(
                        x + org.x, y + org.y, m_seed, 6, 0.5, 256)));

                /*if (h >= org.z)
                    h -= org.z;
                else
                    h = 0;

                if (h < 0)
                    std::cout << "e";
                */

                if (h >= static_cast<int>(16))
                    h = 16;

                if (h != 0) {
                    for (int z = 0; z < h; z++) {
                        float n2 = -1 * Noise::noise3dPerlin(
                                x + org.x, y + org.y, z + org.z, m_seed, 5, 0.5, 128);

                        if (n2 > 0.3f && n2 < 0.7f) {
                            chunk.fill(Voxel { VoxelType::DIRT }, x, y, z);
                        }
                    }
                }
            }
    }
}
