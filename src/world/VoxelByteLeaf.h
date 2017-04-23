#ifndef VOXELBYTELEAF_H
#define VOXELBYTELEAF_H

#include <stdio.h>
#include <vector>
#include "VoxelByte.h"
#include "VoxelByteNote.h"
#include "../draw3d/VoxelRenderer.h"

class VoxelByteLeaf : public VoxelByte
{
  private:
    int x, y, z;
    char voxels[32][32][32];
    GLuint VAO, VBO, EBO;
    const GLfloat *vertices;
    const GLuint *indices;
    std::vector<glm::ivec3> visibleVoxels;
  public:
    void CalculateVisibleVoxels();
    VoxelByteLeaf(int x, int y, int z);
    void Traverse(Camera camera);
    char At(int x, int y, int z);
};

#endif
