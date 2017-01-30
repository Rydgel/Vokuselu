#ifndef VOXELS_MAPGENERATOR_HPP
#define VOXELS_MAPGENERATOR_HPP

#include <iostream>
#include <glm/vec3.hpp>

class Chunk;

class MapGenerator
{
protected :
    int m_seed;
public :
    MapGenerator(int seed = 131183) : m_seed(seed) {}
    virtual ~MapGenerator() { }
    inline int getSeed() const { return m_seed; }
    virtual void makeChunk(Chunk &chunk) = 0;
};

#endif //VOXELS_MAPGENERATOR_HPP
