#ifndef VOXELS_VOXEL_HPP
#define VOXELS_VOXEL_HPP

enum VoxelType
{
    AIR = -1,
    GROUND = 0,
    DIRT = 3,
    STONE = 6,
};

struct Voxel
{
    int type;
};


#endif //VOXELS_VOXEL_HPP
