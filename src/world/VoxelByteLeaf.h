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
    void Traverse(Camera camera);
};

#endif
