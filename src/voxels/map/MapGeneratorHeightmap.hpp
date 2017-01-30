#ifndef VOXELS_MAPGENERATORHEIGHTMAP_HPP
#define VOXELS_MAPGENERATORHEIGHTMAP_HPP

#include "MapGenerator.hpp"
#include "../../utils/noise/Noise.hpp"
#include "../Chunk.hpp"
#include <iostream>
#include <vector>

class MapGenerator;
class MapGeneratorHeightmap : public MapGenerator
{
public :
    MapGeneratorHeightmap(int seed = 131183);
    void makeChunk(Chunk &chunk) override;
};


#endif //VOXELS_MAPGENERATORHEIGHTMAP_HPP
