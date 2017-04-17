#ifndef VOXELBYTE_H
#define VOXELBYTE_H

#include <stdio.h>
#include "../draw3d/VoxelRenderer.h"
#include "../draw3d/Camera.h"

class VoxelByte
{
  protected:
    int x, y, z;
  public:
    virtual void Traverse(Camera camera) = 0;
};

#endif
