#ifndef VOXELBYTELEAF_H
#define VOXELBYTELEAF_H

#include <stdio.h>
#include "VoxelByte.h"
#include "../draw3d/VoxelRenderer.h"

class VoxelByteLeaf : public VoxelByte
{
  private:
    int x, y, z;
    char voxels[32][32][32];
  public:
    VoxelByteLeaf(int x, int y, int z);
    void Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer);
};

#endif
