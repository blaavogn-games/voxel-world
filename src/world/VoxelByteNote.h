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
    static VoxelByteNote *Root;
    VoxelByteNote(int x, int y, int z);
    void CalculateVisibleVoxels(){};
    void Traverse(Camera camera, bool trans);
    char At(int x, int y, int z);
    char At(glm::vec3 &pos);
    void Set(int x, int y, int z, char v);
    void Set(glm::vec3 &pos, char v);
};

#endif
