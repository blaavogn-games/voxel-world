#ifndef VOXELBYTE_H
#define VOXELBYTE_H

#include <stdio.h>
#include "../draw3d/VoxelRenderer.h"

class VoxelByte
{
  private:
    int x, y, z;
    char voxels[32*32];
  public:
    VoxelByte(int x, int y, int z);
    void Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer);
};

#endif
