#ifndef VOXELBYTELEAF_H
#define VOXELBYTELEAF_H

#include <stdio.h>
#include <vector>
#include "VoxelTypes.h"
#include "VoxelByte.h"
#include "VoxelByteNote.h"
#include "../draw3d/VoxelRenderer.h"

class VoxelByteLeaf : public VoxelByte
{
  private:
    int x, y, z;
    char voxels[32][32][32];
    GLuint *VAO, *VBO, *EBO;
    int *sizes;
  public:
    void CalculateVisibleVoxels();
    VoxelByteLeaf(int x, int y, int z);
    ~VoxelByteLeaf();
    void Traverse(Camera camera, bool trans);
    char At(int x, int y, int z);
};

#endif
