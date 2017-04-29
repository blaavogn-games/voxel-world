#ifndef VOXELBYTE_H
#define VOXELBYTE_H

#include <stdio.h>
#include "../draw3d/Camera.h"

class VoxelByte
{
  protected:
    int x, y, z;
  public:
    virtual void CalculateVisibleVoxels() = 0;
    virtual void Traverse(Camera camera, bool trans) = 0;
    virtual char At(int x, int y, int z) = 0;
    virtual void Set(int x, int y, int z, char v) = 0;
};

#endif
