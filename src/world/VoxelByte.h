#ifndef VOXELBYTE_H
#define VOXELBYTE_H

#include <stdio.h>
#include "../draw3d/VoxelRenderer.h"

class VoxelByte
{
  protected:
    int x, y, z;
  public:
    virtual void Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer) = 0;
};

#endif
