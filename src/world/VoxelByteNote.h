#ifndef VOXELBYTENOTE_H
#define VOXELBYTENOTE_H

#include <stdio.h>
#include "VoxelByte.h"
#include "VoxelByteLeaf.h"
#include "../draw3d/VoxelRenderer.h"

class VoxelByteNote : public VoxelByte
{
  private:
    int resolution;
    VoxelByte* voxelBytes[32][32][32];
  public:
    VoxelByteNote(int x, int y, int z);
    void Traverse(int x1, int y1, int z1, int x2, int y2, int z2, VoxelRenderer *voxelRenderer);
};

#endif
